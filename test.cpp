#include "EVP_HMAC_SHA256.h"
#include <stdio.h>
int main(int argc, char **argv){
	char retmsg[64];
	EVP_HMAC_SHA256("45d0b3c26f2644f19bfb98b07741b2f5", "symbol=BTCUSDT&side=BUY&type=LIMIT&quantity=1&price=11&recvWindow=5000&timestamp=1644489390087", retmsg);
	printf("%s\n", retmsg);
	return 0;
}
