#pragma once
#ifndef LM_UITEXT
#define LM_UITEXT
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include "Component.h"

namespace OgreWrapper {
	class UIText;
}

namespace LocoMotor {
	class MOTOR_API UITextLM : public Component {

	public:
		const static std::string name;
		static std::string GetName() {
			return "UIText";
		};

		UITextLM();
		~UITextLM();
		void InitComponent() override;
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		/// @brief Establece la posicion del texto en la pantalla
		void SetPosition(double x, double y);
		/// @brief Establece las dimensiones del texto en la pantalla
		void SetSize(double x, double y);

		/// @brief Cambia el texto a mostrar
		void ChangeText(std::string newtxt);
		/// @brief Establece la altura del texto
		void SetTextHeight(double height);
		/// @brief Establece el tipo de fuente a utilizar
		void SetFont(std::string nfont);
		/// @brief Alinea el texto al centro de la pantalla
		void AlignCenter();
		/// @brief Alinea el texto a la izquierda de la pantalla
		void AlignLeft();
		/// @brief Alinea el texto a la derecha de la pantalla
		void AlignRight();

		/// @brief Establece el color de la parte superior del texto
		/// @param r: componente red
		/// @param g: componente green
		/// @param b: componente blue
		void SetTopColor(double r, double g, double b);
		/// @brief Establece el color de la parte inferior del texto
		/// @param r: componente red
		/// @param g: componente green
		/// @param b: componente blue
		void SetBottomColor(double r, double g, double b);

	protected:
		OgreWrapper::UIText* _uTxt;
		std::string _uFont;
		std::string _uTxtName;

		double posX, posY;
		double sizeX, sizeY;
	};
}
#endif