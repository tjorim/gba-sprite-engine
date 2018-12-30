//
// Created by Vandebosch Remy on 19/12/2018.
//

#include "QuestionBlock.h"

#define bottomHeightFor32 45
#define bottomHeightFor16 29

std::unique_ptr<AffineSprite>& QuestionBlock::getQuestionBlockSprite() {
    return questionBlockSprite;
}

void QuestionBlock::tick(u16 keys) {
    questionBlockSprite->setVelocity(0,0);

    if(keys & KEY_RIGHT) {

        questionBlockSprite->setVelocity(-1, 0);
    }

    if(questionBlockSprite->getX() <=0) questionBlockSprite->moveTo(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT-bottomHeightFor32-30);

}