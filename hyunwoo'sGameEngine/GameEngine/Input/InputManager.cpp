#include "InputManager.h"

bool hyunwoo::InputManager::GetKey(KeyCode keycode) const
{
    char state = _keyStates[int(keycode)];
    return (state & (char)KeyState::DOWN );
}

bool hyunwoo::InputManager::GetKeyUp(KeyCode keycode) const
{
    char state = _keyStates[int(keycode)];
    return (state==(char)KeyState::UP);
}

bool hyunwoo::InputManager::GetKeyDown(KeyCode keycode) const
{
    char state = _keyStates[int(keycode)];
    return (state == (char)KeyState::DOWN);
}

float hyunwoo::InputManager::GetAxisValue(KeyCode minusDirKey, KeyCode plusDirKey) const
{
    float ret = 0.f;
    if (GetKey(minusDirKey)) ret -= 1.f;
    if (GetKey(plusDirKey))  ret += 1.f;

    return ret;
}

void hyunwoo::InputManager::SetKeyState(int keyCode, KeyState state)
{
    const char checkInvalid = ((char)KeyState::Invalid | (char)state);

    if (_keyStates[keyCode] == checkInvalid) return;
    _keyStates[keyCode] = (char)state;
}

void hyunwoo::InputManager::UpdateBuffer()
{
    for (int i = 0; i < 255; i++) {
        char cur = (char)_keyStates[i];
        _keyStates[i] |= (char)KeyState::Invalid;
    }
}
