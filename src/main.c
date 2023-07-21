#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>

void print_usage();

void print_usage()
{
	printf("usage : \n");
	printf("       disk_manager option\n");
}

int main(int argc, const char *argv[])
{
	const unsigned int GB = (1024 * 1024) * 1024;
	struct statvfs buffer;

	if (argc <= 1){
		print_usage();
		exit(0);
	}

    int ret = statvfs(argv[1], &buffer);
    if (!ret) {
		/* Success return 0 */
		const double total = (double)(buffer.f_blocks * buffer.f_frsize) / GB;
		const double available = (double)(buffer.f_bfree * buffer.f_frsize) / GB;
		const double used = total - available;
		const double usedPercentage = (double)(used / total) * (double)100;
		printf("Total: %f GB --> %.0f GB \n", total, total);
		printf("Available: %f GB --> %.0f GB\n", available, available);
		printf("Used: %f GB --> %.1f GB\n", used, used);
		printf("Used Percentage: %f %--> %.0f %\n", usedPercentage, usedPercentage);

		if (usedPercentage >= 95) {
			printf("<I> warning \n");
		}
	}
	else {
		printf("<!> Get Disk size ERROR \n");
		printf("    ret %d \n", ret);
		exit(1);
	}

	return ret;
}
