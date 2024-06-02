#include <stdio.h>
#include <string.h>

// Function to perform brute force string matching
void bruteForceStringMatch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    
    // Loop to slide the pattern over text one by one
    for (int i = 0; i <= n - m; i++) {
        int j;
        
        // For current index i, check for pattern match
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j])
                break;
        }
        
        // If the pattern matches at this index
        if (j == m) {
            printf("Pattern found at index %d\n", i);
        }
    }
}

int main() {
    char text[1000];
    char pattern[100];

    // Input text and pattern from the user
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  // Remove trailing newline

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';  // Remove trailing newline

    // Call the brute force string matching function
    bruteForceStringMatch(text, pattern);
    
    return 0;
}
