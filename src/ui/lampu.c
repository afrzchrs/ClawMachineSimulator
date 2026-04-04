#include "src/ui/lampu.h"

void DrawLampu(Rectangle rec, float roundness, Color color) {
    DrawRectangleRounded((Rectangle){rec.x - 2, rec.y - 2, rec.width + 4, rec.height + 4}, roundness, 20, (Color){30, 30, 30, 255});

    DrawRectangleRounded((Rectangle){rec.x - 8, rec.y - 8, rec.width + 16, rec.height + 16}, roundness, 20, Fade(color, 0.15f));

    DrawRectangleRounded((Rectangle){rec.x - 3, rec.y - 3, rec.width + 6, rec.height + 6}, roundness, 20, Fade(color, 0.50f));

    DrawRectangleRounded(rec, roundness, 20, color);

    Rectangle coreRec = {rec.x + 2, rec.y + 2, rec.width - 4, rec.height - 4};
    DrawRectangleRounded(coreRec, roundness, 20, Fade(WHITE, 0.6f));
}