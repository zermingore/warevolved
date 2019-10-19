bin_PROGRAMS = $(top_srcdir)/we

# Link against pugixml
__top_srcdir__we_LDADD  = ${abs_top_builddir}/lib/libpugixml.a
__top_srcdir__we_LDADD += -lstdc++fs # filesystem


# Source files
__top_srcdir__we_SOURCES =          \
main.cc                             \
\
graphics/GraphicsEngine.cc          \
graphics/Context.cc                 \
graphics/MapGraphicsProperties.cc   \
graphics/Sprite.cc                  \
\
resources/ResourcesManager.cc       \
resources/Resource.cc               \
resources/Font.cc                   \
resources/Text.cc                   \
\
debug/Debug.cc                      \
debug/OSD.cc                        \
\
common/System.cc                    \
\
config/Settings.cc                  \
\
context/State.cc                    \
context/StateGlobal.cc              \
context/StatesFactory.cc            \
context/StatePlaying.cc             \
context/StateMenu.cc                \
context/StateMenuCrew.cc            \
context/StateMovingUnit.cc          \
context/StateSelectTarget.cc        \
context/StateSelectDropZone.cc      \
\
input/KeyManager.cc                 \
input/ReplayManager.cc              \
input/EventManager.cc               \
input/EventsProcessor.cc            \
input/InputsListener.cc             \
input/EventsLogger.cc               \
\
game/Game.cc                        \
game/Status.cc                      \
game/Battle.cc                      \
game/Map.cc                         \
game/Cell.cc                        \
game/Terrain.cc                     \
game/TerrainsHandler.cc             \
game/units/Unit.cc                  \
game/units/UnitsFactory.cc          \
game/units/Vehicle.cc               \
game/units/Car.cc                   \
game/units/Soldier.cc               \
game/Player.cc                      \
game/PathFinding.cc                 \
\
interface/Interface.cc              \
interface/InterfaceSettings.cc      \
interface/InterfaceElement.cc       \
interface/Cursor.cc                 \
interface/Panel.cc                  \
interface/MiniMap.cc                \
interface/menus/Menu.cc             \
interface/menus/MenuEntry.cc        \
interface/menus/MenuEntryCrew.cc    \
interface/menus/InGameMenu.cc       \
interface/menus/MenuMap.cc          \
interface/menus/MenuAction.cc       \
interface/menus/MenuCrew.cc         \
interface/menus/MenuCrewBrowse.cc   \
interface/menus/MenuCrewMember.cc   \
\
tools/StringParser.cc               \
tools/Fps.cc                        \
tools/options/Option.cc             \
tools/options/OptionsParser.cc


# Generated sources files
__top_srcdir__we_SOURCES +=                     \
generated/enum_print/generated_terrains.cc      \
generated/enum_print/generated_path_shapes.cc   \
generated/enum_print/generated_input.cc         \
generated/enum_print/generated_directions.cc    \
generated/enum_print/generated_attack_result.cc \
generated/enum_print/generated_states.cc        \
generated/enum_print/generated_units.cc




# ------------------------------------ Compiler configuration ------------------------------------ #
# setting the __top_srcdir__we_CXXFLAGS variable
__top_srcdir__we_CXXFLAGS = -I${abs_top_builddir}/lib/

# Release flags:
# -s -O3 -DNDEBUG # -Ofast

# Debug flags (no optimization, debug symbols, defines):
__top_srcdir__we_CXXFLAGS += -O0 -g3 -ggdb3 -DDEBUG -DDEBUG_LEAKS # -Og: not clang compliant


# export GLIBCXX_FORCE_NEW


# Append Warning flags
__top_srcdir__we_CXXFLAGS += -Wall                              # Enable most warning messages
__top_srcdir__we_CXXFLAGS += -Wextra                            # Print extra (possibly unwanted) warnings
__top_srcdir__we_CXXFLAGS += -Wpedantic                         # Issue all the warnings demanded by strict ISO C and ISO C++
__top_srcdir__we_CXXFLAGS += -Waggressive-loop-optimizations    # Warn if a loop with constant number of iterations triggers undefined behavior
__top_srcdir__we_CXXFLAGS += -Wformat=2                         # Warn about printf/scanf/strftime/strfmon format string anomalies
__top_srcdir__we_CXXFLAGS += -Wformat-contains-nul              # Warn about format strings that contain NUL bytes
__top_srcdir__we_CXXFLAGS += -Wformat-extra-args                # Warn if passing too many arguments to a function for its format string
__top_srcdir__we_CXXFLAGS += -Wformat-signedness                # Warn about sign differences with format functions
__top_srcdir__we_CXXFLAGS += -Wformat-zero-length               # Warn about zero-length formats
__top_srcdir__we_CXXFLAGS += -Warray-bounds=2                   # Warn if an array is accessed out of bounds # level 1 activated by -Wall (only with -O2); level2: also in structures
__top_srcdir__we_CXXFLAGS += -Wattributes                       # Warn about inappropriate attribute usage
__top_srcdir__we_CXXFLAGS += -Wbool-compare                     # Warn about boolean expression compared with an integer value different from true/false
__top_srcdir__we_CXXFLAGS += -Wbuiltin-macro-redefined          # Warn when a built-in preprocessor macro is undefined or redefined
__top_srcdir__we_CXXFLAGS += -Wcast-align                       # Warn about pointer casts which increase alignment
__top_srcdir__we_CXXFLAGS += -Wcast-qual                        # Warn about casts which discard qualifiers
__top_srcdir__we_CXXFLAGS += -Wconditionally-supported          # Warn for conditionally-supported constructs
__top_srcdir__we_CXXFLAGS += -Wconversion                       # Warn for implicit type conversions that may change a value
__top_srcdir__we_CXXFLAGS += -Wconversion-null                  # Warn for converting NULL from/to a non-pointer type
__top_srcdir__we_CXXFLAGS += -Wctor-dtor-privacy                # Warn when all constructors and destructors are private
__top_srcdir__we_CXXFLAGS += -Wdate-time                        # Warn about __TIME__, __DATE__ and __TIMESTAMP__ usage
__top_srcdir__we_CXXFLAGS += -Wdelete-incomplete                # Warn when deleting a pointer to incomplete type
__top_srcdir__we_CXXFLAGS += -Wdeprecated                       # Warn if a deprecated compiler feature, class, method, or field is used
__top_srcdir__we_CXXFLAGS += -Wdeprecated-declarations          # Warn about uses of __attribute__((deprecated)) declarations
__top_srcdir__we_CXXFLAGS += -Wdisabled-optimization            # Warn when an optimization pass is disabled
__top_srcdir__we_CXXFLAGS += -Wdiv-by-zero                      # Warn about compile-time integer division by zero
__top_srcdir__we_CXXFLAGS += -Wdouble-promotion                 # Warn about implicit conversions from "float" to "double"
__top_srcdir__we_CXXFLAGS += -Wendif-labels                     # Warn about stray tokens after # elif and # endif
__top_srcdir__we_CXXFLAGS += -Wfloat-equal                      # Warn if testing floating point numbers for equality
__top_srcdir__we_CXXFLAGS += -Wfree-nonheap-object              # Warn when attempting to free a non-heap object
__top_srcdir__we_CXXFLAGS += -Winherited-variadic-ctor          # Warn about C++11 inheriting constructors when the base has a variadic constructor
__top_srcdir__we_CXXFLAGS += -Winit-self                        # Warn about variables which are initialized to themselves
__top_srcdir__we_CXXFLAGS += -Winline                           # Warn when an inlined function cannot be inlined
__top_srcdir__we_CXXFLAGS += -Wint-to-pointer-cast              # Warn when there is a cast to a pointer from an integer of a different size
__top_srcdir__we_CXXFLAGS += -Winvalid-memory-model             # Warn when an atomic memory model parameter is known to be outside the valid range.
__top_srcdir__we_CXXFLAGS += -Winvalid-offsetof                 # Warn about invalid uses of the "offsetof" macro
__top_srcdir__we_CXXFLAGS += -Winvalid-pch                      # Warn about PCH files that are found but not used
__top_srcdir__we_CXXFLAGS += -Wlarger-than=4096                 # Warn if an object is larger than <number> bytes
__top_srcdir__we_CXXFLAGS += -Wliteral-suffix                   # Warn when a string or character literal is followed by a ud-suffix which does not begin with an underscore.
__top_srcdir__we_CXXFLAGS += -Wlogical-not-parentheses          # Warn when logical not is used on the left hand side operand of a comparison
__top_srcdir__we_CXXFLAGS += -Wlogical-op                       # Warn when a logical operator is suspiciously always evaluating to true or false
__top_srcdir__we_CXXFLAGS += -Wlong-long                        # Do not warn about using "long long" when -pedantic
__top_srcdir__we_CXXFLAGS += -Wmemset-transposed-args           # Warn about suspicious calls to memset where the third argument is constant literal zero and the second is not
__top_srcdir__we_CXXFLAGS += -Wmissing-declarations             # Warn about global functions without previous declarations
__top_srcdir__we_CXXFLAGS += -Wmissing-include-dirs             # Warn about user-specified include directories that do not exist
__top_srcdir__we_CXXFLAGS += -Wnoexcept                         # Warn when a noexcept expression evaluates to false even though the expression can't actually throw
__top_srcdir__we_CXXFLAGS += -Wnon-template-friend              # Warn when non-templatized friend functions are declared within a template
__top_srcdir__we_CXXFLAGS += -Wnon-virtual-dtor                 # Warn about non-virtual destructors
__top_srcdir__we_CXXFLAGS += -Wnormalized                       # Warn about non-normalised Unicode strings
__top_srcdir__we_CXXFLAGS += -Wodr                              # Warn about some C++ One Definition Rule violations during link time optimization
__top_srcdir__we_CXXFLAGS += -Wold-style-cast                   # Warn if a C-style cast is used in a program
__top_srcdir__we_CXXFLAGS += -Woverflow                         # Warn about overflow in arithmetic expressions
__top_srcdir__we_CXXFLAGS += -Woverloaded-virtual               # Warn about overloaded virtual function names
__top_srcdir__we_CXXFLAGS += -Wpacked                           # Warn when the packed attribute has no effect on struct layout
__top_srcdir__we_CXXFLAGS += -Wpacked-bitfield-compat           # Warn about packed bit-fields whose offset changed in GCC 4.4
__top_srcdir__we_CXXFLAGS += -Wpmf-conversions                  # Warn when converting the type of pointers to member functions
__top_srcdir__we_CXXFLAGS += -Wpragmas                          # Warn about misuses of pragmas
__top_srcdir__we_CXXFLAGS += -Wredundant-decls                  # Warn about multiple declarations of the same object
__top_srcdir__we_CXXFLAGS += -Wreturn-local-addr                # Warn about returning a pointer/reference to a local or temporary variable.
__top_srcdir__we_CXXFLAGS += -Wshadow                           # Warn when one local variable shadows another
__top_srcdir__we_CXXFLAGS += -Wshift-count-negative             # Warn if shift count is negative
__top_srcdir__we_CXXFLAGS += -Wshift-count-overflow             # Warn if shift count >= width of type
__top_srcdir__we_CXXFLAGS += -Wsign-promo                       # Warn when overload promotes from unsigned to signed
__top_srcdir__we_CXXFLAGS += -Wsized-deallocation               # Warn about missing sized deallocation functions
__top_srcdir__we_CXXFLAGS += -Wsizeof-array-argument            # Warn when sizeof is applied on a parameter declared as an array
__top_srcdir__we_CXXFLAGS += -Wsizeof-pointer-memaccess         # Warn about suspicious length parameters to certain string functions if the argument uses sizeof
__top_srcdir__we_CXXFLAGS += -Wstack-protector                  # Warn when not issuing stack smashing protection for some reason
__top_srcdir__we_CXXFLAGS += -Wstrict-null-sentinel             # Warn about uncasted NULL used as sentinel
__top_srcdir__we_CXXFLAGS += -Wstrict-overflow=5                # Warn about optimizations that assume that signed overflow is undefined # (5: overkill ?)
__top_srcdir__we_CXXFLAGS += -Wsuggest-attribute=const          # Warn about functions which might be candidates for __attribute__((const))
__top_srcdir__we_CXXFLAGS += -Wsuggest-attribute=format         # Warn about functions which might be candidates for format attributes
__top_srcdir__we_CXXFLAGS += -Wsuggest-attribute=noreturn       # Warn about functions which might be candidates for __attribute__((noreturn))
__top_srcdir__we_CXXFLAGS += -Wsuggest-attribute=pure           # Warn about functions which might be candidates for __attribute__((pure))
__top_srcdir__we_CXXFLAGS += -Wsuggest-final-methods            # Warn about C++ virtual methods where adding final keyword would improve code quality
__top_srcdir__we_CXXFLAGS += -Wsuggest-final-types              # Warn about C++ polymorphic types where adding final keyword would improve code quality
__top_srcdir__we_CXXFLAGS += -Wsuggest-override                 # Suggest that the override keyword be used when the declaration of a virtual function overrides another.
__top_srcdir__we_CXXFLAGS += -Wswitch-bool                      # Warn about switches with boolean controlling expression
__top_srcdir__we_CXXFLAGS += -Wswitch-default                   # Warn about enumerated switches missing a "default:" statement
__top_srcdir__we_CXXFLAGS += -Wsync-nand                        # Warn when __sync_fetch_and_nand and __sync_nand_and_fetch built-in functions are used
__top_srcdir__we_CXXFLAGS += -Wtrampolines                      # Warn whenever a trampoline is generated
__top_srcdir__we_CXXFLAGS += -Wunsafe-loop-optimizations        # Warn if the loop cannot be optimized due to nontrivial assumptions.
__top_srcdir__we_CXXFLAGS += -Wunused-macros                    # Warn about macros defined in the main file that are not used
__top_srcdir__we_CXXFLAGS += -Wuseless-cast                     # Warn about useless casts
__top_srcdir__we_CXXFLAGS += -Wvarargs                          # Warn about questionable usage of the macros used to retrieve variable arguments
__top_srcdir__we_CXXFLAGS += -Wvector-operation-performance     # Warn when a vector operation is compiled outside the SIMD
__top_srcdir__we_CXXFLAGS += -Wvirtual-move-assign              # Warn if a virtual base has a non-trivial move assignment operator
__top_srcdir__we_CXXFLAGS += -Wwrite-strings                    # In C++, nonzero means warn about deprecated conversion from string literals to 'char *'.
__top_srcdir__we_CXXFLAGS += -Wzero-as-null-pointer-constant    # Warn when a literal '0' is used as null pointer


# Advance Debug
# __top_srcdir__we_CXXFLAGS += -DDEBUG_XML
# __top_srcdir__we_CXXFLAGS += -DDEBUG_XML_FULL
# __top_srcdir__we_CXXFLAGS += -DDEBUG_PERFS


__top_srcdir__we_CXXFLAGS += ${WE_EXTRA_CXXFLAGS}               # Append user-defined flags (for instance -Wno-unknown-warning-option compiling with clang)



#  --all-warnings             This switch lacks documentation
#  --extra-warnings           This switch lacks documentation
#
# Activated by -Wall (C++ relevant):
# ----------------------------------
# -Waddress                   Warn about suspicious uses of memory addresses
# -Wchar-subscripts           Warn about subscripts whose type is "char"
# -Wenum-compare              Warn about comparison of different enum types (default in C++)
# -Wcomment                   Warn about possibly nested block comments, and C++ comments spanning more than one physical line
# -Wformat                    Warn about printf/scanf/strftime/strfmon format string anomalies
# -Wmaybe-uninitialized       Warn about maybe uninitialized automatic variables
# -Wmissing-braces            Warn about possibly missing braces around initializers
# -Wnonnull                   Warn about NULL being passed to argument slots marked as requiring non-NULL
# -Wopenmp-simd               Warn if a simd directive is overridden by the vectorizer cost model
# -Wparentheses               Warn about possibly missing parentheses
# -Wpointer-sign              Warn when a pointer differs in signedness in an assignment
# -Wreorder                   Warn when the compiler reorders code
# -Wreturn-type               Warn whenever a function's return type defaults to "int" (C), or about inconsistent return types (C++)
# -Wsequence-point            Warn about possible violations of sequence point rules
# -Wsign-compare              Warn about signed-unsigned comparisons
# -Wunused                    Enable all -Wunused- warnings
# -Wunused-variable           Warn when a variable is unused
# -Wunused-function           Warn when a function is unused
# -Wunused-value              Warn when an expression value is unused
# -Wunused-label              Warn when a label is unused
# -Wunused-local-typedefs     Warn when typedefs locally defined in a function are not used
# -Wunused-but-set-variable   Warn when a variable is only set, otherwise unused
# -Wswitch                    Warn about enumerated switches, with no default, missing a case
# -Wtrigraphs                 Warn if trigraphs are encountered that might affect the meaning of the program
# -Wuninitialized             Warn about uninitialized automatic variables
# -Wunknown-pragmas           Warn about unrecognized pragmas
# -Wvolatile-register-var     Warn when a register variable is declared volatile
# -Wstrict-aliasing           Warn about code which might break strict aliasing rules
# -Wstrict-overflow           Warn about optimizations that assume that signed overflow is undefined
# -Wmultichar                 Warn about use of multi-character character constants
# -Wmisleading-indentation    Warn about miss-leading identation (with blocks without braces)
#
#
#  Activated by -Wextra (C++ relevant):
#  ------------------------------------
# -Wignored-qualifiers        Warn whenever type qualifiers are ignored.
# -Wclobbered                 Warn about variables that might be changed by "longjmp" or "vfork"
# -Wempty-body                Warn about an empty body in an if or else statement
# -Wmissing-field-initializers Warn about missing fields in struct initializers
# -Woverride-init             Warn about overriding initializers without side effects
# -Wtype-limits               Warn if a comparison is always true or always false due to the limited range of the data type
# -Wunused-parameter          Warn when a function parameter is unused
# -Wunused-but-set-parameter  Warn when a function parameter is only set, otherwise unused
#
#
#  Activated by -Wpedantic (C++ relevant):
#  ---------------------------------------
# -Wvla                       Warn if a variable length array is used
# -Wpointer-arith             Warn about function pointer arithmetic
# -Woverlength-strings        Warn if a string is longer than the maximum portable length specified by the standard



# Note:
# -W is deprecated: use -Wextra
# -Wunreachable-code seems to have been removed
# Clang has a -Weverything not g++
# -Wnon-virtual-dtor is activated by -Weffc++ (unfortunately the latest gives too many false-positives so far)


# Deactivated warnings
# -Wundef                     Warn if an undefined macro is used in an # if directive
# -Wsystem-headers            Do not suppress warnings from system headers
# -Waggregate-return          Warn about returning structures, unions or arrays
# -Wswitch-enum               Warn about all enumerated switches missing a specific case (even if a 'default' is present)
# -Weffc++                    Warn about violations of Effective C++ style rules (05/2017: too many false positives [std::string default constructor])

# Deactivated warnings (unsure about the relevance in this context)
# -Wpadded                    Warn when padding is required to align structure members
# -Wcpp                       Warn when a # warning directive is encountered (seems active by default)
# -Wstack-usage=4096          Warn if stack usage might be larger than specified amount
