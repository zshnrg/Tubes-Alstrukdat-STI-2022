#include <stdio.h>
#include "scoreboardtype.h"

int getValFromIdx(Scoreboard SB, int Idx) {
    return Value(SB.Score, SB.Nama.Elements[Idx]);
}

void sortSet(Scoreboard *SB) {
    if (!IsEmptySet((*SB).Nama)) {
        for (int i = 0; i < (*SB).Nama.Count; i++) {
            Word minName = (*SB).Nama.Elements[0];
            int minVal = Value((*SB).Score, minName);
            for (int j = 1; j < (*SB).Nama.Count - i; j++) {
                int compVal = getValFromIdx(*SB, j);
                if (minVal < compVal) {
                    minName = (*SB).Nama.Elements[j];
                    minVal = compVal;
                } 
            }
            DeleteSet(&((*SB).Nama), minName);
            InsertSet(&((*SB).Nama), minName);
        }
    }
}