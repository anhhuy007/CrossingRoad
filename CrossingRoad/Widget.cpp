#include "Widget.h"
#include <map>

const std::map<char, std::string> punctuations = {
	{'.', "dot"},
	{',', "comma"},
	{'!', "exclamation"},
	{'?', "question"},
	{'-', "hyphen"},
	{'_', "underscore"},
	{'@', "at"},
	{'#', "hash"},
	{'$', "dollar"},
	{'%', "percent"},
	{'&', "ampersand"},
	{'*', "asterisk"},
	{'(', "left_parenthesis"},
	{')', "right_parenthesis"},
	{'=', "equal"},
	{'+', "plus"},
	{'|', "vertical_bar"},
	{'{', "left_brace"},
	{'}', "right_brace"},
	{'[', "left_bracket"},
	{']', "right_bracket"},
	{'<', "less_than"},
	{'>', "greater_than"},
	{'~', "tilde"},
	{'`', "grave_accent"},
	{':', "colon"},
	{';', "semicolon"},
	{'^', "caret"},
	{'\"', "quotation"},
	{' ', "space"}
};

Widget::Text::Text(
	CrossingRoad* pgame,
	std::string ptext,
	COORD pposition,
	int pwidth,
	int pheight,
	TextFont pfont
) : GameObject(pgame) {
	if (ptext == "") return;

	ptext += " ";
	text = ptext;
	font = pfont;
	position = pposition;
	width = pwidth;
	height = pheight;

	// set appearance
	appearance.clear();
	for (auto& ch : ptext) {
		// get sprite name
		if (!isalpha(ch) && !isdigit(ch)) continue;

		std::string spriteName = GetLetterSpritePath(ch, font);
		Image letter = Image(spriteName, Overlapped::TEXT);
		appearance.push_back(letter);
	}

	// set text positions
	SetTextPosition(ptext, pposition, pwidth, pheight);
};

Widget::Text::Text(
	CrossingRoad* pgame,
	std::string ptext,
	COORD pposition,
	int pwidth,
	int pheight,
	TextFont pfont,
	short pcolor
) : GameObject(pgame) {
	if (ptext == "") return;

	ptext += " ";
	text = ptext;
	font = pfont;
	color = pcolor;
	position = pposition;
	width = pwidth;
	height = pheight;

	// set appearance
	appearance.clear();
	for (auto& ch : ptext) {
		// get sprite name
		if (!isalpha(ch) && !isdigit(ch)) continue;

		std::string spriteName = GetLetterSpritePath(ch, font);
		Image letter = Image(spriteName, Overlapped::TEXT);
		appearance.push_back(letter);
	}

	// set text positions
	SetTextPosition(ptext, pposition, pwidth, pheight);
	SetTextColor(pcolor);
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
	case TextFont::NUMBER:
		path += "numbers\\numbers\\";
		break;
	case TextFont::COIN_NUMBER:
		path += "numbers\\coin_numbers\\";
		break;
	}

	// change to lowercase
	if (letter >= 'a' && letter <= 'z') {
		letter -= 32;
	}

	// check if letter is punctuation
	else if (punctuations.find(letter) != punctuations.end()) {
		path += punctuations.at(letter);
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

int Widget::GetWordWidth(std::string word, int letterWidth) {
	return word.size() * letterWidth + LETTER_SPACE; // 2 pixels is space between 2 letters
}

void Widget::Text::Render() {
	for (int i = 0; i < appearance.size(); i++) {
		game->RenderSprite(appearance[i], textPositions[i]);
	}
}

void Widget::Text::UpdateText(std::string ptext)
{
	if (ptext == text || ptext == "") return;
	ptext += " ";
	text = ptext;

	// set appearance
	appearance.clear();
	for (auto& ch : ptext) {
		// get sprite name
		if (!isalpha(ch) && !isdigit(ch)) continue;

		std::string spriteName = GetLetterSpritePath(ch, font);
		Image letter = Image(spriteName, Overlapped::TEXT);
		appearance.push_back(letter);
	}

	// set text positions
	SetTextPosition(ptext, position, width, height);
	SetTextColor(color);
}

void Widget::Text::UpdatePosition(COORD pposition)
{
	position = pposition;
	SetTextPosition(text, position, width, height);
}

void Widget::Text::SetTextPosition(
	std::string ptext,
	COORD pposition,
	int pwidth,
	int pheight
) {
	textPositions.clear();

	int wordHeight = appearance[0].GetHeight();
	int maxX = pposition.X + pwidth;
	int maxY = pposition.Y + pheight;
	COORD currentPos = pposition;
	int index = 0;
	while (index < ptext.size()) {
		std::string word = GetNextWord(index, ptext);
		int wordWidth = GetWordWidth(word, appearance[0].GetWidth());

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
			currentPos.X += appearance[i].GetWidth();
		}
		currentPos.X += 2; // 2 pixels is space between 2 words

		index += word.size() + 1;
	}
}

void Widget::Text::SetTextColor(short pcolor)
{
	for (auto& letter : appearance) {	
		for (int i = 0; i < letter.GetHeight(); i++) {
			for (int j = 0; j < letter.GetWidth(); j++) {
				if (letter.GetPixel(i, j).color != COLOR::TRANSPARENT_) {
					letter.SetPixelColor(i, j, pcolor);
				}
			}
		}
	}
}

Widget::Button::Button(
	CrossingRoad* pgame,
	std::string ptext,
	std::function<void()> paction,
	COORD pposition
) : GameObject(pgame) {

	text = Text(
		pgame,
		ptext,
		GetCenterTextPos(
			ptext,
			{ short(pposition.X + 43), short(pposition.Y + 18) },
			90, 22
		),
		90, 22,
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
	game->sound->playEffectSound(int(Sound::Effect::ENTER));
}

void Widget::Button::OnHover() {
	state = ButtonState::ON_HOVER;
}

void Widget::Button::OnNormal() {
	state = ButtonState::NORMAL;
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
	int textWidth = GetWordWidth(text, 5);
	int textHeight = 5;

	int x = position.X + (width - textWidth) / 2;
	int y = position.Y + (height - textHeight) / 2;

	return { short(x), short(y) };
}

COORD Widget::GetMessageImgPos(
	COORD position,
	int width,
	int height,
	int imgWidth,
	int imgHeight
) {
	int x = position.X + (width - imgWidth) / 2;
	int y = position.Y + (height - imgHeight) / 2;

	return { short(x), short(y) };
}

Widget::Dialog::Dialog(
	CrossingRoad* pgame, 
	std::string ptext, 
	std::vector<Widget::Button>& pbuttons, 
	COORD pposition
) : GameObject(pgame) {
	dialog = Image(DrawableRes::Dialog, Overlapped::DIALOG);
	width = dialog.GetWidth();
	height = dialog.GetHeight();

	message = Widget::Text(
		pgame,
		ptext,
		Widget::GetCenterTextPos(
			ptext, 
			{ short(pposition.X + 65), short(pposition.Y + 10) }, // {pposition.X + 65, pposition.Y + 15
			width - 65, height - 50
		),
		width - 65,
		height - 50,
		TextFont::NORMAL
	);
	buttons = pbuttons;
	position = pposition;

	// change buttons appearances
	for (auto& button : buttons) {
		button.appearance[0] = Image(DrawableRes::DialogButtonNormal, Overlapped::BUTTON);
		button.appearance[1] = Image(DrawableRes::DialogButtonHover, Overlapped::BUTTON);
		button.appearance[2] = Image(DrawableRes::DialogButtonHover, Overlapped::BUTTON);
	}

	// set button positions
	COORD pos = {pposition.X + 72, pposition.Y + 45 };
	if (buttons.size() == 2) pos.X += 30;
	for (auto& button : buttons) {
		button.setPosition(pos);

		// set button text positions
		button.text.SetTextPosition(
			button.text.text,
			Widget::GetMessageImgPos(
				pos,
				57, 13,
				button.text.text.length() * 5, 5
			),
			57, 13
		);

		pos.X += 60;
	}
}

Widget::Dialog::Dialog(
	CrossingRoad* pgame,
	Image _pdialog,
	Image _pmessageImage,
	std::vector<Widget::Button>& pbuttons,
	COORD pposition
) : GameObject(pgame) {
	dialog = _pdialog;
	dialogMessage = _pmessageImage;
	buttons = pbuttons;
	position = pposition;
	width = dialog.GetWidth();
	height = dialog.GetHeight();

	// change buttons appearances
	for (auto& button : buttons) {
		button.appearance[0] = Image(DrawableRes::DialogButtonNormal, Overlapped::BUTTON);
		button.appearance[1] = Image(DrawableRes::DialogButtonHover, Overlapped::BUTTON);
		button.appearance[2] = Image(DrawableRes::DialogButtonHover, Overlapped::BUTTON);
	}

	// set button positions
	COORD pos = { pposition.X + 72, pposition.Y + 45 };
	if (buttons.size() == 2) pos.X += 30;
	for (auto& button : buttons) {
		button.setPosition(pos);

		// set button text positions
		button.text.SetTextPosition(
			button.text.text,
			Widget::GetMessageImgPos(
				pos,
				57, 13,
				button.text.text.length() * 5, 5
			),
			57, 13
		);

		pos.X += 60;
	}
}

void Widget::Dialog::Update(float elapsedTime) {
	auto checkIndex = [max = (int)buttons.size() - 1, _game = game](int& i) {
		if (i < 0 || i > max) {
			_game->sound->playEffectSound(int(Sound::Effect::INVALID));
			i = max(0, i);
			i = min(max, i);
			return 0;
		}
		_game->sound->playEffectSound(int(Sound::Effect::VALID));
		return 1;
		};
	// get key pressed events
	if (game->inputHandle->keyState_[Keyboard::LEFT_KEY].isPressed) {
		checkIndex(--currentButtonIndex);
	}
	else if (game->inputHandle->keyState_[Keyboard::RIGHT_KEY].isPressed) {
		checkIndex(++currentButtonIndex);
	}
	else if (game->inputHandle->keyState_[Keyboard::ENTER_KEY].isPressed) {
		enterClicked = true;
		game->sound->playEffectSound(int(Sound::Effect::ENTER));
	}

	// update button state
	for (int i = 0; i < buttons.size(); i++) {
		if (i == currentButtonIndex) {
			if (enterClicked) {
				game->sound->playEffectSound(int(Sound::Effect::ENTER));

			}
			else {
				buttons[i].OnHover();
			}
		}
		else {
			buttons[i].OnNormal();
		}
	}

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Render();
	}

	// trigger button action
	if (enterClicked) {
		totalTime += elapsedTime;
		//if (totalTime > 100) {
			enterClicked = false;
			buttons[currentButtonIndex].action();
			totalTime = 0;
		//}
	}
}

void Widget::Dialog::Render() {
	game->RenderSprite(dialog, position);

	int imgWidth = dialogMessage.GetWidth();
	int imgHeight = dialogMessage.GetHeight();
	game->RenderSprite(
		dialogMessage, 
		GetMessageImgPos(
			{ short(position.X + 65), position.Y },
			dialog.GetWidth() - 65, dialog.GetHeight() - 30,
			imgWidth, imgHeight
		)
	);

	message.Render();
	for (auto& button : buttons) {
		button.Render();
	}
}
