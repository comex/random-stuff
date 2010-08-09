GCC = /Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/gcc-4.2 -arch armv6 -isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS3.2.sdk/ 
vn: vn.c
	$(GCC) -o $@ $^
clean:
	rm -f vn
