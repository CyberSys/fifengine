%module model
%{
#include "model/metamodel/object.h"
%}

%include "util/attributedclass.i"

namespace FIFE { namespace model {

	class Action;

	class Object : public AttributedClass {
		public:

			~Object();

			template<typename T>
			const T& oget(const std::string& field);
			%template(oget_bool) oget<bool>;
			%template(oget_int) oget<long>;
			%template(ogetPoint) oget<Point>;
			%template(ogetRect) oget<Rect>;
			%template(oget_string) oget<std::string>;

			Action* addAction(const std::string& action_name);
			Action* getAction(const std::string& action_name);

		private:

			Object(const Object* inherited);
	};
}}
