//#include <stdbool.h>
//#include <string.h>
//#include <iso646.h>
//
//typedef struct {
//	bool** map;
//	bool** tempMap;
//	int startX;
//	int endX;
//	int startY;
//	int endY;
//} golArgs;

//static inline int checkCell(int x, int y) {
//	if (x < 0 or y < 0 or x > MAP_X - 1 or y > MAP_Y - 1) {
//		return 0;
//	}
//	else {
//		return map[x][y];
//	}
//}

//void celluralAutomata()
//{
//	for (int x = 0; x < MAP_X; x++) {
//		for (int y = 0; y < MAP_Y; y++) {
//			int neighbours = 0;
//
//			neighbours += checkCell(x - 1, y);
//			neighbours += checkCell(x - 1, y + 1);
//			neighbours += checkCell(x - 1, y - 1);
//			neighbours += checkCell(x + 1, y);
//			neighbours += checkCell(x + 1, y + 1);
//			neighbours += checkCell(x + 1, y - 1);
//			neighbours += checkCell(x, y + 1);
//			neighbours += checkCell(x, y - 1);
//
//			if (neighbours == 3) {
//				tempMap[x][y] = true;
//			}
//			else if (neighbours == 2) {
//				tempMap[x][y] = map[x][y];
//			}
//			else {
//				tempMap[x][y] = false;
//			}
//
//		}
//	}
//	for (int x = 0; x < MAP_X; x++) {
//		memcpy(map[x], tempMap[x], MAP_Y * sizeof(bool));
//	}
//}