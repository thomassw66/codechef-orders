#include <iostream>

#define MAX_INPUT_SIZE 200000

int main(int argc, char const *argv[]) {

        int test_cases;
        int soldiers;
        int input[MAX_INPUT_SIZE+1];
        int output[MAX_INPUT_SIZE+1];
        int dec[MAX_INPUT_SIZE+1];
        int count;

        std::ios_base::sync_with_stdio(false);

        // NOTE: This answer is wrong (example input: [0, 1, 1] )

        std::cin >> test_cases;
        while (test_cases) {
                std::cin >> soldiers;

                for (int i = 1; i < soldiers+1; i++) {
                        std::cin >> input[i];
                }
                for (int i = 1; i < soldiers+1; i++) {
                        dec[i] = 0;
                }
                count = 0;
                for (int i = soldiers; i >= 1; i--) {

                        output[i] = i + count - input[i];
                        count++;
                        dec[i - input[i]]++;
                        count -= dec[i];
                }
                for (int i = 1; i < soldiers+1; i++) {
                        std::cout << output[i];
                        std::cout << " ";
                }
                std::cout << '\n';
                test_cases--;
        }

        return 0;
}
