#include <stdio.h>

// int main(int argc, char **argv) {
//     const char hexstring[] = "DEadbeef10203040b00b1e50", *pos = hexstring;
//     unsigned char val[12];

//     /* WARNING: no sanitization or error-checking whatsoever */
//     for (size_t count = 0; count < sizeof val / sizeof * val; count++) {
//         sscanf(pos, "%2hhx", &val[count]);
//         pos += 2;
//     }

    
//     for (size_t count = 0; count < sizeof val / sizeof * val; count++) {
//         printf("0x");
//         printf("%02x", val[count]);

//         printf("\n");

//         uint8_t tint = val[count];
//         uint8_t stale = ("0x%2x", val[count]);
//         printf("%02x", tint);
//         printf("\n");
//         printf("%02x", stale);
//         printf("\n");
//     }
// }