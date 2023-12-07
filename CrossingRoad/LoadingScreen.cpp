#include "LoadingScreen.h"

bool LoadingScreen::OnCreate()
{
    InitWidget();
    return true;
}

bool LoadingScreen::OnUpdate(float elapsedTime)
{
    time += elapsedTime;

    if (time > 3000) return false;

    game->RenderSprite(bgImage, { 0, 0 });
    game->RenderSprite(tip, { 194, 128 });
    loadingAnimation.OnPlay(elapsedTime);
    chickAnimation.OnPlay(elapsedTime);

    return true;
}

void LoadingScreen::InitWidget()
{
    // chick animation
    std::vector<Image> chickSprites;
    for (int i = 0; i < 9; i++) {
        std::string path = DrawableRes::chickLoadingAnimationFolder + "frame" + std::to_string(i) + ".sprite";
        chickSprites.push_back(Image(path, Overlapped::DECORATOR));
    }

    // loading animation
    std::vector<Image> loadingSprites = {
        Image(DrawableRes::Loading1, Overlapped::DECORATOR),
        Image(DrawableRes::Loading2, Overlapped::DECORATOR),
        Image(DrawableRes::Loading3, Overlapped::DECORATOR)
    };

    bgImage = Image(DrawableRes::BlueLoadingBG, Overlapped::BACKGROUND);
    int randomTip = rand() % 5 + 1;
    std::string tipPath = "widgets\\Tip" + std::to_string(randomTip) + ".sprite";
    tip = Image(tipPath, Overlapped::DECORATOR);

    chickAnimation = Animation(game, chickSprites, { 102, 75 }, 70);
    loadingAnimation = Animation(game, loadingSprites, { 194,105 }, 400);

    // set console colors
    std::vector<int> colors = {
        RGB(0, 0, 0), 
        RGB(255, 255, 255), 
        RGB(105, 206, 236), 
        RGB(94, 193, 225),
        RGB(47, 2, 31), 
        RGB(245, 228, 238), 
        RGB(255, 150, 111), 
        RGB(235, 90, 87),
        RGB(255, 110, 165), 
        RGB(229, 60, 117),  
        RGB(126, 74, 76), 
        RGB(255, 112, 51),
        RGB(65, 39, 42), 
        RGB(255, 59, 69), 
        RGB(176, 40, 49), 
        RGB(77, 18, 30)
    };

    game->SetConsoleColor(colors);
}
