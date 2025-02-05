#include <iostream>
#include <regex>
#include <string>
#include <fstream>

int main() {






    std::ifstream ifs("input.txt");
    if (!ifs) {
        std::cerr << "Could not open input.txt\n";
        return 1;
    }

    // Read the entire file buffer into an ostringstream
    std::ostringstream oss;
    oss << ifs.rdbuf();

    // Convert that stream into a std::string
    std::string contents = oss.str();

    // Now 'contents' holds the file’s full text, including newlines,
    // with *no* extra interpretation of backslashes or anything else.
    std::cout << "File contents:\n" << contents << std::endl;


    std::string mulClause   = R"(mul\((\d+),(\d+)\))"; 
    std::string doClause    = R"(do\(\))"; 
    std::string dontClause  = R"(don't\(\))";
    std::string combinedPattern = 
        "(?:" + mulClause + 
        "|"   + doClause + 
        "|"   + dontClause + 
        ")";

    std::regex re(combinedPattern);

    // Use std::sregex_iterator to find all matches
    auto begin = std::sregex_iterator(contents.begin(), contents.end(), re);
    auto end   = std::sregex_iterator();


    long ans = 0;
    bool active = true;
    // Iterate over matches
    for (auto it = begin; it != end; ++it) {
        std::smatch match = *it;

        std::cout << "Matched: " << match[0].str() << "\n";

        if (match[0].str() == "don't()") active = false;
        if (match[0].str() == "do()") active = true;

        if (match[0].str()[0] == 'm' && active) {
          ans += std::stoi(match[1].str()) * std::stoi(match[2].str());
        }


        
    }

    std::cout << ans << std::endl;

    return 0;
}
