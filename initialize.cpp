#define C_NONE 0//棋子：黑子,白子,无子

#define C_BLACK 1

#define C_WHITE 2



//棋型代号 下标 权重

#define OTHER 0//0,其他棋型不考虑

#define WIN 1//100000,白赢

#define LOSE 2//-10000000

#define FLEX4 3//50000,白活4

#define flex4 4//-80000

#define BLOCK4 5//400

#define block4 6//-80000

#define FLEX3 7//400

#define flex3 8//-8000

#define BLOCK3 9//20

#define block3 10//-40

#define FLEX2 11//20

#define flex2 12//-40

#define BLOCK2 13//1

#define block2 14//-2

#define FLEX1 15//1

#define flex1 16//-2

#define C_NONE 0//棋子：黑子,白子,无子

#define C_BLACK 1

#define C_WHITE 2



	//棋型代号 下标 权重

#define OTHER 0//0,其他棋型不考虑

#define WIN 1//100000,白赢

#define LOSE 2//-10000000

#define FLEX4 3//50000,白活4

#define flex4 4//-80000

#define BLOCK4 5//400

#define block4 6//-80000

#define FLEX3 7//400

#define flex3 8//-8000

#define BLOCK3 9//20

#define block3 10//-40

#define FLEX2 11//20

#define flex2 12//-40

#define BLOCK2 13//1

#define block2 14//-2

#define FLEX1 15//1

#define flex1 16//-2
	
#include<iostream>
using namespace std;
int type[4][4][4][4][4][4];

void chess::init_type() {
	memset(type, 0, sizeof(type));
	type[2][2][2][2][2][2] = WIN;
	type[2][2][2][2][2][0] = WIN;
	type[0][2][2][2][2][2] = WIN;
	type[2][2][2][2][2][1] = WIN;
	type[1][2][2][2][2][2] = WIN;
	type[3][2][2][2][2][2] = WIN;//边界考虑
	type[2][2][2][2][2][3] = WIN;
	//黑连5，ai输
	type[1][1][1][1][1][1] = LOSE;
	type[1][1][1][1][1][0] = LOSE;
	type[0][1][1][1][1][1] = LOSE;
	type[1][1][1][1][1][2] = LOSE;
	type[2][1][1][1][1][1] = LOSE;
	type[3][1][1][1][1][1] = LOSE;
	type[1][1][1][1][1][3] = LOSE;
	//白活4
	type[0][2][2][2][2][0] = FLEX4;
	//黑活4
	type[0][1][1][1][1][0] = flex4;
//白活3
	type[0][2][2][2][0][0] = FLEX3;
	type[0][0][2][2][2][0] = FLEX3;
	type[0][2][0][2][2][0] = FLEX3;
	type[0][2][2][0][2][0] = FLEX3;
	//黑活3
	type[0][1][1][1][0][0] = flex3;
	type[0][0][1][1][1][0] = flex3;
	type[0][1][0][1][1][0] = flex3;
	type[0][1][1][0][1][0] = flex3;
	//白活2
	type[0][2][2][0][0][0] = FLEX2;
	type[0][2][0][2][0][0] = FLEX2;
	type[0][2][0][0][2][0] = FLEX2;
	type[0][0][2][2][0][0] = FLEX2;
	type[0][0][2][0][2][0] = FLEX2;
	type[0][0][0][2][2][0] = FLEX2;
	//黑活2
	type[0][1][1][0][0][0] = flex2;
	type[0][1][0][1][0][0] = flex2;
	type[0][1][0][0][1][1] = flex2;
	type[0][0][1][1][0][0] = flex2;
	type[0][0][1][0][1][0] = flex2;
	type[0][0][0][1][1][0] = flex2;
	//白活1
	type[0][2][0][0][0][0] = FLEX1;
	type[0][0][2][0][0][0] = FLEX1;
	type[0][0][0][2][0][0] = FLEX1;
	type[0][0][0][0][2][0] = FLEX1;
	//黑活1
	type[0][1][0][0][0][0] = flex1;
	type[0][0][1][0][0][0] = flex1;
	type[0][0][0][1][0][0] = flex1;
	type[0][0][0][0][1][0] = flex1;

	int p1, p2, p3, p4, p5, p6, x, y, ix, iy;//x:左边5个格子中黑子个数，y:左边5个格子中白字个数,ix:右边5个中黑子个数,iy:右边5个格子中白字个数
	for (p1 = 0; p1 < 4; ++p1) {
		for (p2 = 0; p2 < 3; ++p2) {
			for (p3 = 0; p3 < 3; ++p3) {
				for (p4 = 0; p4 < 3; ++p4) {
					for (p5 = 0; p5 < 3; ++p5) {
						for (p6 = 0; p6 < 4; ++p6) {
							x = y = ix = iy = 0;
							if (p1 == 1)x++;
							else if (p1 == 2)y++;

							if (p2 == 1) { x++; y++; }
							else if (p2 == 2) { x++; y++; }

							if (p3 == 1) { x++; ix++; }
							else if (p3 == 2) { y++; iy++; }

							if (p4 == 1) { x++; ix++; }
							else if (p4 == 2) { y++; iy++; }

							if (p5 == 1) { x++; ix++; }
							else if (p5 == 2) { y++; iy++; }

							if (p6 == 1)ix++;
							else if (p6 == 2)iy++;

							if (p1 == 3 || p6 == 3) {//有边界
								if (p1 == 3 && p6 != 3) {//左边界
								//白冲4
									if (ix == 0 && iy == 4) {//若右边有活4无妨，因为活4的权重远大于冲4
										if (type[p1][p2][p3][p4][p5][6] == 0)
											type[p1][p2][p3][p4][p5][p6] = BLOCK4;

									}
									//黑冲4
									if (ix == 4 && iy == 0) {
										if (type[p1][p2][p3][p4][p5][6] == 0)
											type[p1][p2][p3][p4][p5][6] == block4;

									}
									//白眠3
									if (ix == 0 && iy == 3) {
										if (type[p1][p2][p3][p4][p5][6] == 0)
											type[p1][p2][p3][p4][p5][6] == BLOCK3;
									}
									//黑眠3
									if (ix == 3 && iy == 0) {
										if (type[p1][p2][p3][p4][p5][6] == 0)
											type[p1][p2][p3][p4][p5][6] == block3;
									}
									//白眠2
									if (ix == 0 && iy == 2) {
										if (type[p1][p2][p3][p4][p5][6] == 0)
											type[p1][p2][p3][p4][p5][6] == BLOCK2;
									}




								}
								else if (p6 == 3 && p1 != 3) {//有边界
									//白冲4
									if (x == 0 && y == 4) {
										if (type[p1][p2][p3][p4][p5][6] == 0)
											type[p1][p2][p3][p4][p5][6] == BLOCK4;

									}
									//黑冲4
									if (x == 4 && y == 0) {
										if (type[p1][p2][p3][p4][p5][6] == 0)
											type[p1][p2][p3][p4][p5][6] == block4;


									}
									//黑眠3
									if (x == 3 && y == 0) {
										if (type[p1][p2][p3][p4][p5][6] == 0)
											type[p1][p2][p3][p4][p5][6] == BLOCK3;
									}
									//白眠3
									if (x == 0 && y == 3) {
										if (type[p1][p2][p3][p4][p5][6] == 0)
											type[p1][p2][p3][p4][p5][6] == block3;
									}
									//黑眠2
									if (x == 2 && y == 0) {
										if (type[p1][p2][p3][p4][p5][6] == 0)
											type[p1][p2][p3][p4][p5][6] == BLOCK2;
									}
									//白眠2
									if (x == 0 && y == 2) {
										if (type[p1][p2][p3][p4][p5][6] == 0)
											type[p1][p2][p3][p4][p5][6] == block2;
									}


								}
							}
							else {//无边界
								//白冲4
								if ((x == 0 && y == 4) || (ix == 0 && iy == 4)) {
									if (type[p1][p2][p3][p4][p5][6] == 0)
										type[p1][p2][p3][p4][p5][6] == BLOCK4;
								}
								//黑冲4
								if ((x == 4 && y == 0) || (ix == 4 && iy == 0)) {
									if (type[p1][p2][p3][p4][p5][6] == 0)
										type[p1][p2][p3][p4][p5][6] == block4;
								}
								//白眠3
								if ((x == 0 && y == 3) || (ix == 0 && iy == 3)) {
									if (type[p1][p2][p3][p4][p5][6] == 0)
										type[p1][p2][p3][p4][p5][6] == BLOCK3;
								}
								//黑眠3
								if ((x == 3 && y == 0) || (ix == 3 && iy == 0)) {
									if (type[p1][p2][p3][p4][p5][6] == 0)
										type[p1][p2][p3][p4][p5][6] == block3;
								}
								//白眠2
								if ((x == 0 && y == 2) || (ix == 0 && iy == 2)) {
									if (type[p1][p2][p3][p4][p5][6] == 0)
										type[p1][p2][p3][p4][p5][6] == BLOCK2;
								}
								//黑眠2
								if ((x == 2 && y == 0) || (ix == 2 && iy == 0)) {
									if (type[p1][p2][p3][p4][p5][6] == 0)
										type[p1][p2][p3][p4][p5][6] == block2;
								}


							}
						}
					}
				}
			}
		}

	}