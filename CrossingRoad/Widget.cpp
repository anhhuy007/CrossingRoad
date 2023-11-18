#include "Widget.h"

Widget::Text::Text(
	CrossingRoad* pgame,
	std::string ptext,
	COORD pposition,
	int pwidth,
	int pheight,
	TextFont pfont
) : GameObject(pgame) {
	ptext += " ";
	text = ptext;
	font = pfont;
	position = pposition;

	// set appearance
	appearance.clear();
	for (auto& ch : ptext) {
		// get sprite name
		if (!isalpha(ch)) continue;

		std::string spriteName = GetLetterSpritePath(ch, font);
		Image letter = Image(spriteName, Overlapped::TEXT);
		appearance.push_back(letter);
	}

	// set text positions
	setTextPosition(ptext, pposition, pwidth, pheight);
};

std::string Widget::Text::GetLetterSpritePath(char letter, TextFont font) {
	std::string path = "alphabet\\";
	switch (font) {
	case TextFont::TITLE:
		path += "title\\";
		break;
	case TextFont::NORMAL:
		path += "normal\\";
		break;
	}

	// change to lowercase
	if (letter >= 'a' && letter <= 'z') {
		letter -= 32;
	}

	path = path + letter + ".sprite";

	return path;
}


std::string Widget::Text::GetNextWord(int index, std::string ptext) {
	std::string ans = "";
	while (ptext[index] != ' ') {
		ans += ptext[index];
		index++;
	}

	return ans;
}

int Widget::Text::GetWordWidth(std::string word) {
	return word.size() * appearance[0].getWidth() + LETTER_SPACE; // 2 pixels is space between 2 letters
}

void Widget::Text::Render() {
	for (int i = 0; i < appearance.size(); i++) {
		game->RenderSprite(appearance[i], textPositions[i]);
	}
}

void Widget::Text::setTextPosition(std::string ptext, COORD pposition, int pwidth, int pheight) {
	textPositions.clear();

	int wordHeight = appearance[0].getHeight();
	int maxX = pposition.X + pwidth;
	int maxY = pposition.Y + pheight;
	COORD currentPos = pposition;
	int index = 0;
	while (index < ptext.size()) {
		std::string word = GetNextWord(index, ptext);
		int wordWidth = GetWordWidth(word);

		if (currentPos.X + wordWidth > maxX) {
			// if text box is full then stop writing text
			if (currentPos.Y + wordHeight > maxY) continue;

			// go to the begin of new line
			currentPos.X = pposition.X;
			currentPos.Y += wordHeight + 3;
		}

		// set each character positions
		for (int i = 0; i < word.size(); i++) {
			textPositions.push_back(currentPos);
			currentPos.X += appearance[i].getWidth();
		}
		currentPos.X += 2; // 2 pixels is space between 2 words

		index += word.size() + 1;
	}
}

Widget::Button::Button(
	CrossingRoad* pgame, 
	std::string ptext, 
	function<void()> paction, 
	COORD pposition
) : GameObject(pgame) {
	
	text = Text(
		pgame, 
		ptext, 
		GetCenterTextPos(ptext, pposition, 112, 34),
		112, 34,
		TextFont::NORMAL
	);

	action = paction;
	position = pposition;
	state = ButtonState::NORMAL;

	appearance.clear();
	appearance.push_back(Image(DrawableRes::normalButton, Overlapped::DECORATOR));
	appearance.push_back(Image(DrawableRes::onChosenButton, Overlapped::DECORATOR));
	appearance.push_back(Image(DrawableRes::onEnterButton, Overlapped::DECORATOR));
}

void Widget::Button::OnTrigger() {
	if (state == ButtonState::ON_TRIGGER) return;

	state = ButtonState::ON_TRIGGER;

	// move text down
	COORD textPos = text.getPosition();
	for (int i = 0; i < text.textPositions.size(); i++) {
		text.textPositions[i].Y += 3;
	}
	
	// play sfx 
	// game->sound->PlaySfx(Sfx::BUTTON_HOVER);
}

void Widget::Button::OnHover() {
	state = ButtonState::ON_HOVER;
}

void Widget::Button::OnNormal() {
	state = ButtonState::NORMAL;
}

void Widget::Button::Update(float elapsedTime) {
	Render();
	if (state == ButtonState::ON_TRIGGER) {
		// wait for 0.5s to show triggered animation and playing sfx
		game->UpdateConsole();

		action();
	}
	
}

void Widget::Button::Render() {
	text.Render();
	if (state == ButtonState::NORMAL) {
		game->RenderSprite(appearance[0], position);
	}
	else if (state == ButtonState::ON_HOVER) {
		game->RenderSprite(appearance[1], position);
	}
	else if (state == ButtonState::ON_TRIGGER) {
		game->RenderSprite(appearance[2], position);
	}
}

COORD Widget::GetCenterTextPos(
	std::string text, 
	COORD position, 
	int width, 
	int height
) {
	int textWidth = text.size() * 5;
	int textHeight = 5;

	int x = position.X + (width - textWidth) / 2;
	int y = position.Y + (height - textHeight) / 2;

	return { short(x + 20), short(y + 10) };
}
