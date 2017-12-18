//
// Created by Guanqi Yu on 12/16/17.
//

#include <string>
#include <vector>

#ifndef CPPPRIMER_SCREEN_H
#define CPPPRIMER_SCRREN_H

/**
 * if a const member function return *this as a reference, the return type would be a const reference type
 * can't myScreen.display().set('#');
 *
 * when a member function call another function, this pointer is implicitly passed
 * const Screen blank(5, 3);
 * blank(cout); // const object can only call const member function
 * Screen myScreen(3, 5);
 * myScreen.set('#').display(cout); // non-const object call non-const member function
 */

// define member function as friend
class Screen; // forward declaration, Screen is a incomplete type now
class Window_mgr {
public:
	using ScreenIdx = std::vector::size_type ;
	void clear(ScreenIdx);
	ScreenIdx addScreen(const Screen&);
private:
	std::vector<Screen> screens;
};

class Screen {
	friend void Window_mgr::clear(ScreenIdx);
public:
//	typedef std::string::size_type pos;
	using pos = std::string::size_type;
	Screen() = default;
	Screen(pos ht, pos wd, char c) :
			height(ht), width(wd), contents(ht * wd, c) { }

	char get() const { return contents[cursor]; }
	char get(pos r, pos c) const;
	Screen &move(pos r, pos c);
	void some_member() const;
	Screen &set(char);
	// const overload
	Screen &display(std::ostream &os) // this change from Salesdata *const this to const Salesdata *const this
					{ do_display(os); return *this; }
	const Screen &display(std::ostream &os) const
					{ do_display(os); return *this; }
private:
	void do_display(std::ostream &os) const { os << contents; }
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
	mutable access_ctr;
};

inline
char Screen::get(pos r, pos c) const {
	pos row = r * width;
	return contents[row + c];
}

inline
Screen &Screen::move(pos r, pos c) {
	pos row = r * width;
	cursor = row + c;
	return *this;
}

inline
void Screen::some_member() const {
	++access_ctr;
}

/**
 * return reference of the object who called set. usage:
 * mScreen.move(4, 0).set('#')
 *
 * otherwise:
 * Screen tmp = myScreen.move(4, 0);
 * temp.set('#'); ---> change the temp value, not original value
 */
inline Screen &Screen::set(char c) {
	contents[cursor] = c;
	return *this;
}

inline
void Window_mgr::clear(ScreenIdx idx) {
	Screen &s = screens[idx];
	s.contents = std::string(s.height * s.width, ' ');
}

/**
 * since return tyoe occurs before the function name, when member function defined out of the class,
 * the return type is out of the class's function area, so has to specify which class the type belongs to
 */
Window_mgr::ScreenIdx
Window_mgr::addScreen(const Screen &s) {
	screens.push_back(s);
	return screens.size() - 1;
}

#endif