#include "../lib/sandpile.h"
#include "../lib/ArgParser.h"

int main(int argc, char** argv) {
    Sandpile sandpile;

    ArgumentParser::ArgParser parser("SandPile Parser");

    parser.AddIntArgument('l', "length").StoreValue(sandpile.length).Default(0);
    parser.AddIntArgument('w', "width").StoreValue(sandpile.width).Default(0);
    parser.AddStringArgument('i', "input").StoreValue(sandpile.tsv_path);
    parser.AddStringArgument('o', "output").StoreValue(sandpile.out_path).Default("./");
    parser.AddIntArgument('m', "max-freq").StoreValue(sandpile.max_iter).Default(INT64_MAX);
    parser.AddIntArgument('f', "freq").StoreValue(sandpile.freq).Default(0);

    parser.Parse(argc, argv);

    sandpile.setFromTSV(sandpile.tsv_path);
    sandpile.spilling();

    return 0;
}
