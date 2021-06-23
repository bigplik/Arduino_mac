  // .setTextSize(1);        // 21 char/line (fills 1st & 2nd lines in yellow) 8 lines Max
  // .setTextSize(2);        // 10 char/line (fills 1st line in yellow)        4 lines Max
  // .setTextSize(3);        //  7 char/line (overflows 1st yellow into Blue)
			
	.setTextSize(1) == 21 characters x 8 lines

	Line1		012345678901234567890
	Line2		012345678901234567890
	Line3		012345678901234567890
	Line4		012345678901234567890
	Line5		012345678901234567890
	Line6		012345678901234567890
	Line7		012345678901234567890
	Line8		012345678901234567890
			^^^^^^^^^^^^^^^^^^^^^
			123456789111111111122
			         012345678901


			128x64 Pixel Matrix
			
			0,0		127,0
			0,1		127,1
			~~~		~~~~~
			~~~		~~~~~
			0,62		127,62
			0,63		127,63

