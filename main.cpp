#include "common-sdl.h"
#include "common.h"
#include "whisper.h"
#include "grammar-parser.h"

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
// Include the Whisper library


// command-line parameters
struct whisper_params {
    int32_t n_threads  = std::min(4, (int32_t) std::thread::hardware_concurrency());
    int32_t prompt_ms  = 5000;
    int32_t command_ms = 8000;
    int32_t capture_id = -1;
    int32_t max_tokens = 32;
    int32_t audio_ctx  = 0;

    float vad_thold  = 0.6f;
    float freq_thold = 100.0f;

    float grammar_penalty = 100.0f;

    grammar_parser::parse_state grammar_parsed;

    bool translate     = false;
    bool print_special = false;
    bool print_energy  = false;
    bool no_timestamps = true;
    bool use_gpu       = true;
    bool flash_attn    = false;

    std::string language  = "en";
    std::string model     = "models/ggml-tiny.en.bin";
    std::string fname_out;
    std::string commands;
    std::string prompt;
    std::string context;
    std::string grammar;

    // A regular expression that matches tokens to suppress
    std::string suppress_regex;
};

void whisper_print_usage(int argc, char ** argv, const whisper_params & params);

static bool whisper_params_parse(int argc, char ** argv, whisper_params & params) {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            whisper_print_usage(argc, argv, params);
            exit(0);
        }
        else if (arg == "-t"   || arg == "--threads")       { params.n_threads     = std::stoi(argv[++i]); }
        else if (arg == "-pms" || arg == "--prompt-ms")     { params.prompt_ms     = std::stoi(argv[++i]); }
        else if (arg == "-cms" || arg == "--command-ms")    { params.command_ms    = std::stoi(argv[++i]); }
        else if (arg == "-c"   || arg == "--capture")       { params.capture_id    = std::stoi(argv[++i]); }
        else if (arg == "-mt"  || arg == "--max-tokens")    { params.max_tokens    = std::stoi(argv[++i]); }
        else if (arg == "-ac"  || arg == "--audio-ctx")     { params.audio_ctx     = std::stoi(argv[++i]); }
        else if (arg == "-vth" || arg == "--vad-thold")     { params.vad_thold     = std::stof(argv[++i]); }
        else if (arg == "-fth" || arg == "--freq-thold")    { params.freq_thold    = std::stof(argv[++i]); }
        else if (arg == "-tr"  || arg == "--translate")     { params.translate     = true; }
        else if (arg == "-ps"  || arg == "--print-special") { params.print_special = true; }
        else if (arg == "-pe"  || arg == "--print-energy")  { params.print_energy  = true; }
        else if (arg == "-ng"  || arg == "--no-gpu")        { params.use_gpu       = false; }
        else if (arg == "-fa"  || arg == "--flash-attn")    { params.flash_attn    = true; }
        else if (arg == "-l"   || arg == "--language")      { params.language      = argv[++i]; }
        else if (arg == "-m"   || arg == "--model")         { params.model         = argv[++i]; }
        else if (arg == "-f"   || arg == "--file")          { params.fname_out     = argv[++i]; }
        else if (arg == "-cmd" || arg == "--commands")      { params.commands      = argv[++i]; }
        else if (arg == "-p"   || arg == "--prompt")        { params.prompt        = argv[++i]; }
        else if (arg == "-ctx" || arg == "--context")       { params.context       = argv[++i]; }
        else if (                 arg == "--grammar")       { params.grammar       = argv[++i]; }
        else if (                 arg == "--grammar-penalty") { params.grammar_penalty = std::stof(argv[++i]); }
        else if (                 arg == "--suppress-regex") { params.suppress_regex = argv[++i]; }
        else {
            fprintf(stderr, "error: unknown argument: %s\n", arg.c_str());
            whisper_print_usage(argc, argv, params);
            exit(0);
        }
    }

    return true;
}

// Function to calculate the Levenshtein distance between two strings
int levenshteinDistance(const std::string &s1, const std::string &s2) {
    int m = s1.size();
    int n = s2.size();
    std::vector<std::vector<int>> d(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                d[i][j] = j;
            } else if (j == 0) {
                d[i][j] = i;
            } else {
                int cost = (s1[i - 1] != s2[j - 1]) ? 1 : 0;
                d[i][j] = std::min({d[i - 1][j - 1] + cost, d[i][j - 1] + 1, d[i - 1][j] + 1});
            }
        }
    }

    return d[m][n];
}

// Function to have a 10 second countdown in the console:
void countdown() {
    for (int i = 10; i > 0; i--) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Time's up!" << std::endl;
}

// Function to say Hello to the user in the console:
void sayHello() {
    std::cout << "Hello!" << std::endl;
}

// Function to process voice commands
void processVoiceCommand(const std::string &command) {
    if (command == "hello") {
        sayHello();
    } else if (command == "countdown") {
        countdown();
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }
}

int main(int argc, char **argv) {
    whisper_params params;

    if (whisper_params_parse(argc, argv, params) == false) {
        return 1;
    }

    if (whisper_lang_id(params.language.c_str()) == -1) {
        fprintf(stderr, "error: unknown language '%s'\n", params.language.c_str());
        whisper_print_usage(argc, argv, params);
        exit(0);
    }

    // whisper init
    struct whisper_context_params cparams = whisper_context_default_params();
    cparams.use_gpu = params.use_gpu;
    cparams.flash_attn = params.flash_attn;

    struct whisper_context *ctx = whisper_init_from_file_with_params(params.model.c_str(), cparams);

    // init audio
    audio_async audio(30 * 1000);
    if (!audio.init(params.capture_id, WHISPER_SAMPLE_RATE)) {
        fprintf(stderr, "%s: audio.init() failed!\n", __func__);
        return 1;
    }

    audio.resume();

    // wait for 1 second to avoid any buffered noise
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    audio.clear();

    std::cout << "Press CTRL-C to exit." << std::endl;

    bool is_running = true;
    std::vector<float> pcmf32_cur;

    while (is_running) {
        // handle Ctrl + C
        is_running = sdl_poll_events();

        // delay
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        audio.get(2000, pcmf32_cur);

        if (::vad_simple(pcmf32_cur, WHISPER_SAMPLE_RATE, 1000, params.vad_thold, params.freq_thold, params.print_energy)) {
            fprintf(stdout, "%s: Speech detected! Processing ...\n", __func__);

            int64_t t_ms = 0;
            float logprob_min = 0.0f;
            float logprob_sum = 0.0f;
            int n_tokens = 0;

            const auto txt = ::trim(::transcribe(ctx, params, pcmf32_cur, "", logprob_min, logprob_sum, n_tokens, t_ms));

            processVoiceCommand(txt);

            audio.clear();
        }
    }

    audio.pause();
    whisper_print_timings(ctx);
    whisper_free(ctx);

    return 0;
}