#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QColor>

class IInputMethod;

class PlayerController
{
	public:
		PlayerController(const QColor &color, IInputMethod *inputMethod);
		~PlayerController();

		QColor color() const;

		IInputMethod *inputMethod() const;

		void toggleReady();

		bool isReady() const;

	private:
		QColor m_color;

		IInputMethod *m_inputMethod;

		bool m_ready;
};

#endif // PLAYERCONTROLLER_H
