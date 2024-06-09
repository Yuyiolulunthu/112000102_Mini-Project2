#include <allegro5/allegro_primitives.h>
#include "Input.hpp"
#include "Engine/Resources.hpp"
#include "Engine/Point.hpp"

namespace Engine {
	TextInput::TextInput(const std::string& font, int fontSize, float x, float y, int width, int height, unsigned char r, unsigned char g, unsigned char b, unsigned char a, unsigned char br, unsigned char bg, unsigned char bb, unsigned char ba, float anchorX, float anchorY) :
		IObject(x, y, width, height, anchorX, anchorY), font(Resources::GetInstance().GetFont(font, fontSize)), Text("Your name"), Color(al_map_rgba(255, 255, 255, 255)), BackgroundColor(al_map_rgba(0, 0, 0, 0)), Focused(false), Width(width), Height(height) {
	}

	void TextInput::Draw() const {
		// Draw background
		al_draw_filled_rectangle(Position.x - Anchor.x * Width, Position.y - Anchor.y * Height,
			Position.x + (1 - Anchor.x) * Width, Position.y + (1 - Anchor.y) * Height, BackgroundColor);
		// Draw text
		al_draw_text(font.get(), Color, Position.x - Anchor.x * Width, Position.y - Anchor.y * Height, 0, Text.c_str());
		al_draw_rectangle(Position.x - Anchor.x * Width, Position.y - Anchor.y * Height, Position.x - Anchor.x * Width + Width, Position.y - Anchor.y * Height + Height, al_map_rgb(255, 255, 255), 1.0);

	}

	void TextInput::SetText(const std::string& text) {
		Text = text;
	}

	std::string TextInput::GetText() const {
		return Text;
	}

	void TextInput::OnFocus() {
		Focused = true;
	}

	void TextInput::OnBlur() {
		Focused = false;
	}

	void TextInput::OnKeyPress(int keycode) {
		printf("%d\n", keycode);
		// if (Focused) {
			if (keycode == ALLEGRO_KEY_BACKSPACE && !Text.empty()) {
				Text.pop_back();
			} else if (keycode >= ALLEGRO_KEY_A && keycode <= ALLEGRO_KEY_Z) {
				Text += static_cast<char>(keycode + 'a' - ALLEGRO_KEY_A);
			}
		// }
	}
}
