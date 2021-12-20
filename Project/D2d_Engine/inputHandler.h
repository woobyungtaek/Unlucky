#pragma once

/****************************************************************************************
* Author:	Gilles Bellot
* Date:		31/05/2018 - Lenningen - Luxembourg
*
* Desc:		Event based input handler
*
* History:	- 05/06/2018: added keyboard support
*			- 11/06/2018: added mouse support
****************************************************************************************/

// INCLUDES /////////////////////////////////////////////////////////////////////////////

// Windows and COM
#include <Windows.h>

// c++ containers
#include <unordered_map>
#include <array>

// bell0bytes utilities
//#include "expected.h"

// CLASSES //////////////////////////////////////////////////////////////////////////////
namespace graphics
{
	class AnimatedSprite;
}

namespace input
{
	// enumerate all game commands
	enum Events : int;																// enumeration of all standard application events
	enum GameCommands : int;														// enumeration of all possible game commands
	enum KeyState { StillReleased, JustPressed, StillPressed, JustReleased };		// enumeration of all possible key states
	
	// structure to combine key codes and key states
	// each game command can have several bindings (chord), i.e. toggle show FPS = 'shift'+'control'+'FPS'
	struct BindInfo
	{
	private:
		unsigned int keyCode;		// the actual key code
		KeyState keyState;			// the state the above specified key has to be in for the "binding" to become active
	
	public:
		// constructors and destructor
		BindInfo();
		BindInfo(const unsigned int keyCode, const KeyState keyState);
		~BindInfo() {};

		friend struct GameCommand;
		friend class InputHandler;
	};

	// structure to map a single game command to a chord of key strokes (see above)
	struct GameCommand
	{
	private:
		std::wstring name;						// human readable name
		std::vector<BindInfo> chord;			// the chord mapped to this command, i.e. "shift"+"control"+"F"

	public:
		// constructors and destructor
		GameCommand();
		GameCommand(const std::wstring& name, const unsigned int keyCode, const KeyState keyState);
		GameCommand(const std::wstring& name, const BindInfo& bi);
		GameCommand(const std::wstring& name, const std::vector<BindInfo>& chord);
		~GameCommand() {};

		friend class InputHandler;
	};

	// the keyboard and mouse class
	class KeyboardAndMouse
	{
	private:
		std::array<bool, 256> currentState;					// the state of the keyboard keys and mouse buttons in the current frame
		std::array<bool, 256> previousState;				// the state of the keyboard keys and mouse buttons in the previous frame

		graphics::AnimatedSprite* mouseCursor;				// the sprite of the mouse cursor

		long mouseX, mouseY;								// the position of the mouse cursor

	public:
		KeyboardAndMouse();
		KeyboardAndMouse(graphics::AnimatedSprite* const mouseCursor);
		~KeyboardAndMouse();
		
		friend class InputHandler;
	};

	// the main input handler class
	class InputHandler
	{
	private:
		/////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////// GENERAL //////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		bool activeKeyboard;										// true iff keyboard input is active
		bool activeMouse;											// true iff mouse input is active

		// polling
		void update();												// update the active key map
		
		/////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////// KEYBOARD AND MOUSE ////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		KeyboardAndMouse* kbm;										// pointer to keyboard and mouse class							
		
		void getKeyboardAndMouseState();									// gets the keyboard and mouse button state, uses GetAsyncKeyState to read the state of all 256 keys
		const KeyState getKeyState(const unsigned int keyCode) const;		// gets the state of the specified key, depending on its state in the previous and the current frame
		inline const bool isPressed(int keyCode) const { return (GetAsyncKeyState(keyCode) & 0x8000) ? 1 : 0; };	// returns true iff the key is down
		
	protected:
		std::unordered_map<GameCommands, GameCommand*> keyMap;		// list of all possible game commands mapped to the appropriate command structure
		
		// constructor and destructor
		InputHandler();
		~InputHandler();

		// initialization
		virtual void setDefaultKeyMap() = 0;						// set up default controls

		// getters and setters

		//util::Expected<std::wstring> getKeyName(const unsigned int keyCode);// retrieves the name of a virtual key code

	public:
		/////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////// GENERAL //////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		std::unordered_map<GameCommands, GameCommand*> activeKeyMap;// list of all active key maps; game acts on each command in this list

		void acquireInput();										// reads the state of the game controllers
		
		/////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////// KEYBOARD AND MOUSE ////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		void drawMouseCursor() const;								// draws the mouse cursor
		void setMouseCursor(graphics::AnimatedSprite* const mouseCursor) { this->kbm->mouseCursor = mouseCursor; };
		void changeMouseCursorAnimationCycle(const unsigned int cycle);	
		void updateMouseCursorAnimation(const double deltaTime);
	};
}