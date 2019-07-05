#include "GLuaUtil.h"

void PrintStack(GarrysMod::Lua::ILuaBase* luabase) {
	int n = luabase->Top();

	printf("------------------------- STACK TRACE -------------------------\n");

	for (int idx = 1; idx < n; idx++) {

		int positive = n - idx;
		int negative = -(idx + 1);

		int t = luabase->GetType(positive);
		int tn = luabase->GetType(negative);

		assert(t == tn);

		using namespace GarrysMod::Lua;

		switch (t) {
		case Type::NIL:
			printf("%d/%d: NIL\n", positive, negative);
			break;
		case Type::BOOL:
			printf("%d/%d: %s\n", positive, negative, luabase->GetBool(positive) ? "true" : "false");
			break;
		case Type::NONE:
			printf("%d/%d: NONE\n", positive, negative);
			break;
		case Type::NUMBER:
			printf("%d/%d: %g\n", positive, negative, luabase->GetNumber(positive));
			break;
		case Type::ENTITY:
			printf("%d/%d: ENTITY\n", positive, negative);
			break;
		case Type::FUNCTION:
			printf("%d/%d: FUNCTION\n", positive, negative);
			break;
		case Type::TABLE:
			printf("%d/%d: TABLE\n", positive, negative);
			break;
		case Type::STRING:
			printf("%d/%d: STRING: %s\n", positive, negative, luabase->GetString(positive));
		default:
			printf("%d/%d: %s\n", positive, negative, luabase->GetTypeName(positive));
			break;
		}
	}

	printf("-------------------------- END TRACE --------------------------\n");
	return;
}
