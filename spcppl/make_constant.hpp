#define MAKE_CONSTANT(name, type) \
		struct name { \
			static type value; \
		}; \
		type name::value;
