bin_PROGRAMS = $(top_srcdir)/we

# Link against pugixml
__top_srcdir__we_LDADD  = ${abs_top_builddir}/lib/libpugixml.a
__top_srcdir__we_LDADD += -lstdc++fs # filesystem

# Setting the __top_srcdir__we_CXXFLAGS variable
__top_srcdir__we_CXXFLAGS = -I${abs_top_builddir}/lib/


# Different main() if testing or not
if UNIT_TESTS
  __top_srcdir__we_SOURCES = ${abs_top_builddir}/tests/unit/main.cc
  __top_srcdir__we_CXXFLAGS += -I${abs_top_builddir}/tests/unit/lib/
else
  __top_srcdir__we_SOURCES = main.cc
endif


# Source files
__top_srcdir__we_SOURCES +=              \
graphics/GraphicsEngine.cc               \
graphics/Context.cc                      \
graphics/Properties.cc                   \
graphics/Sprite.cc                       \
\
resources/ResourcesManager.cc            \
resources/Font.cc                        \
resources/Text.cc                        \
\
debug/Debug.cc                           \
debug/OSD.cc                             \
\
config/Settings.cc                       \
\
context/State.cc                         \
context/StateGlobal.cc                   \
context/StatesFactory.cc                 \
context/StatePlaying.cc                  \
context/StateEditMap.cc                  \
context/StateMenu.cc                     \
context/StateMenu2d.cc                   \
context/StateMovingUnit.cc               \
context/StateSelectCell.cc               \
context/StateSelectTarget.cc             \
context/StateSelectDropZone.cc           \
context/StateSelectExitZone.cc           \
context/StateInventory.cc                \
\
input/KeyManager.cc                      \
input/ReplayManager.cc                   \
input/EventManager.cc                    \
input/EventsProcessor.cc                 \
input/InputsListener.cc                  \
\
game/Game.cc                             \
game/Status.cc                           \
game/Battle.cc                           \
game/Map.cc                              \
game/Terrain.cc                          \
game/TerrainsHandler.cc                  \
game/units/Unit.cc                       \
game/units/UnitsFactory.cc               \
game/units/Vehicle.cc                    \
game/units/Car.cc                        \
game/units/Motorcycle.cc                 \
game/units/Soldier.cc                    \
game/Player.cc                           \
game/PathFinding.cc                      \
game/Building.cc                         \
game/Inventory.cc                        \
game/ItemsContainer.cc                   \
game/Item.cc                             \
\
interface/Interface.cc                   \
interface/InterfaceElement.cc            \
interface/Cursor.cc                      \
interface/Panel.cc                       \
interface/MiniMap.cc                     \
interface/menus/Menu.cc                  \
interface/menus/MenuEntry.cc             \
interface/menus/InGameMenu.cc            \
interface/menus/MenuMap.cc               \
interface/menus/MenuAction.cc            \
interface/menus/MenuCrew.cc              \
interface/menus/MenuBuilding.cc          \
\
tools/StringParser.cc                    \
tools/Fps.cc                             \
tools/Random.cc                          \
tools/options/Option.cc                  \
tools/options/OptionsParser.cc


# Generated sources files
__top_srcdir__we_SOURCES +=          \
  generated/enum_print/enum_print.cc




# ------------------------------------ Compiler configuration ------------------------------------ #
# Release flags:
# -s -O3 -DNDEBUG # -Ofast

# Debug flags (no optimization, debug symbols, defines):
__top_srcdir__we_CXXFLAGS += -O0 -g3 -ggdb3 -DDEBUG -DDEBUG_LEAKS # -Og: not clang compliant


# export GLIBCXX_FORCE_NEW


__top_srcdir__we_CXXFLAGS += -Waddress-of-packed-member                     # Warn when the address of packed member of struct or union is taken.
__top_srcdir__we_CXXFLAGS += -Waggressive-loop-optimizations                # Warn if a loop with constant number of iterations triggers undefined behavior.
__top_srcdir__we_CXXFLAGS += -Wall                                          # Enable most warning messages.
__top_srcdir__we_CXXFLAGS += -Walloc-zero                                   # Warn for calls to allocation functions that specify zero bytes.
__top_srcdir__we_CXXFLAGS += -Walloca                                       # Warn on any use of alloca.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-double-fclose                       # Warn about code paths in which a stdio FILE can be closed more than once.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-double-free                         # Warn about code paths in which a pointer can be freed more than once.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-exposure-through-output-file        # Warn about code paths in which sensitive data is written to a file.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-file-leak                           # Warn about code paths in which a stdio FILE is not closed.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-free-of-non-heap                    # Warn about code paths in which a non-heap pointer is freed.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-malloc-leak                         # Warn about code paths in which a heap-allocated pointer leaks.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-null-argument                       # Warn about code paths in which NULL is passed to a must-not-be-NULL function argument.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-null-dereference                    # Warn about code paths in which a NULL pointer is dereferenced.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-possible-null-argument              # Warn about code paths in which a possibly-NULL value is passed to a must-not-be-NULL function argument.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-possible-null-dereference           # Warn about code paths in which a possibly-NULL pointer is dereferenced.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-stale-setjmp-buffer                 # Warn about code paths in which a longjmp rewinds to a jmp_buf saved in a stack frame that has returned.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-tainted-array-index                 # Warn about code paths in which an unsanitized value is used as an array index.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-too-complex                         # Warn if the code is too complicated for the analyzer to fully explore.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-unsafe-call-within-signal-handler   # Warn about code paths in which an async-signal-unsafe function is called from a signal handler.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-use-after-free                      # Warn about code paths in which a freed value is used.
__top_srcdir__we_CXXFLAGS += -Wanalyzer-use-of-pointer-in-stale-stack-frame # Warn about code paths in which a pointer to a stale stack frame is used.
__top_srcdir__we_CXXFLAGS += -Warith-conversion                             # Warn if conversion of the result of arithmetic might change the value even though converting the operands cannot.
__top_srcdir__we_CXXFLAGS += -Wattribute-alias                              # Warn about type safety and similar errors and mismatches in declarations with alias attributes.  Same as -Wattribute-alias=.
__top_srcdir__we_CXXFLAGS += -Wattribute-warning                            # Warn about uses of __attribute__((warning)) declarations.
__top_srcdir__we_CXXFLAGS += -Wattributes                                   # Warn about inappropriate attribute usage.
__top_srcdir__we_CXXFLAGS += -Wbool-compare                                 # Warn about boolean expression compared with an integer value different from true/false.
__top_srcdir__we_CXXFLAGS += -Wbool-operation                               # Warn about certain operations on boolean expressions.
__top_srcdir__we_CXXFLAGS += -Wbuiltin-declaration-mismatch                 # Warn when a built-in function is declared with the wrong signature.
__top_srcdir__we_CXXFLAGS += -Wbuiltin-macro-redefined                      # Warn when a built-in preprocessor macro is undefined or redefined.
__top_srcdir__we_CXXFLAGS += -Wcannot-profile                               # Warn when profiling instrumentation was requested, but could not be applied to a certain function.
__top_srcdir__we_CXXFLAGS += -Wcast-align                                   # Warn about pointer casts which increase alignment.
__top_srcdir__we_CXXFLAGS += -Wcast-align=strict                            # Warn about pointer casts which increase alignment.
__top_srcdir__we_CXXFLAGS += -Wcast-function-type                           # Warn about casts between incompatible function types.
__top_srcdir__we_CXXFLAGS += -Wcast-qual                                    # Warn about casts which discard qualifiers.
__top_srcdir__we_CXXFLAGS += -Wcatch-value                                  # Warn about catch handlers of non-reference type.  Same as -Wcatch-value=.
__top_srcdir__we_CXXFLAGS += -Wclass-conversion                             # Warn when a conversion function will never be called due to the type it converts to.
__top_srcdir__we_CXXFLAGS += -Wclass-memaccess                              # Warn for unsafe raw memory writes to objects of class types.
__top_srcdir__we_CXXFLAGS += -Wcomma-subscript                              # Warn about uses of a comma operator within a subscripting expression.
__top_srcdir__we_CXXFLAGS += -Wcomments                                     # Synonym for -Wcomment.  Same as -Wcomment.
__top_srcdir__we_CXXFLAGS += -Wconditionally-supported                      # Warn for conditionally-supported constructs.
__top_srcdir__we_CXXFLAGS += -Wconversion                                   # Warn for implicit type conversions that may change a value.
__top_srcdir__we_CXXFLAGS += -Wconversion-null                              # Warn for converting NULL from/to a non-pointer type.
__top_srcdir__we_CXXFLAGS += -Wcoverage-mismatch                            # Warn in case profiles in -fprofile-use do not match.
__top_srcdir__we_CXXFLAGS += -Wcpp                                          # Warn when a #warning directive is encountered.
__top_srcdir__we_CXXFLAGS += -Wctor-dtor-privacy                            # Warn when all constructors and destructors are private.
__top_srcdir__we_CXXFLAGS += -Wdangling-else                                # Warn about dangling else.
__top_srcdir__we_CXXFLAGS += -Wdate-time                                    # Warn about __TIME__, __DATE__ and __TIMESTAMP__ usage.
__top_srcdir__we_CXXFLAGS += -Wdelete-incomplete                            # Warn when deleting a pointer to incomplete type.
__top_srcdir__we_CXXFLAGS += -Wdeprecated                                   # Warn if a deprecated compiler feature, class, method, or field is used.
__top_srcdir__we_CXXFLAGS += -Wdeprecated-copy                              # Mark implicitly-declared copy operations as deprecated if the class has a user-provided copy operation.
__top_srcdir__we_CXXFLAGS += -Wdeprecated-copy-dtor                         # Mark implicitly-declared copy operations as deprecated if the class has a user-provided copy operation or destructor.
__top_srcdir__we_CXXFLAGS += -Wdeprecated-declarations                      # Warn about uses of __attribute__((deprecated)) declarations.
__top_srcdir__we_CXXFLAGS += -Wdisabled-optimization                        # Warn when an optimization pass is disabled.
__top_srcdir__we_CXXFLAGS += -Wdiv-by-zero                                  # Warn about compile-time integer division by zero.
__top_srcdir__we_CXXFLAGS += -Wdouble-promotion                             # Warn about implicit conversions from "float" to "double".
__top_srcdir__we_CXXFLAGS += -Wduplicated-branches                          # Warn about duplicated branches in if-else statements.
__top_srcdir__we_CXXFLAGS += -Wduplicated-cond                              # Warn about duplicated conditions in an if-else-if chain.
__top_srcdir__we_CXXFLAGS += -Wendif-labels                                 # Warn about stray tokens after #else and #endif.
__top_srcdir__we_CXXFLAGS += -Wexpansion-to-defined                         # Warn if "defined" is used outside #if.
__top_srcdir__we_CXXFLAGS += -Wextra                                        # Print extra (possibly unwanted) warnings.
__top_srcdir__we_CXXFLAGS += -Wextra-semi                                   # Warn about semicolon after in-class function definition.
__top_srcdir__we_CXXFLAGS += -Wfloat-conversion                             # Warn for implicit type conversions that cause loss of floating point precision.
__top_srcdir__we_CXXFLAGS += -Wfloat-equal                                  # Warn if testing floating point numbers for equality.
__top_srcdir__we_CXXFLAGS += -Wformat-contains-nul                          # Warn about format strings that contain NUL bytes.
__top_srcdir__we_CXXFLAGS += -Wformat-diag                                  # Warn about GCC format strings with strings unsuitable for diagnostics.
__top_srcdir__we_CXXFLAGS += -Wformat-extra-args                            # Warn if passing too many arguments to a function for its format string.
__top_srcdir__we_CXXFLAGS += -Wformat-nonliteral                            # Warn about format strings that are not literals.
__top_srcdir__we_CXXFLAGS += -Wformat-security                              # Warn about possible security problems with format functions.
__top_srcdir__we_CXXFLAGS += -Wformat-signedness                            # Warn about sign differences with format functions.
__top_srcdir__we_CXXFLAGS += -Wformat-truncation                            # Warn about calls to snprintf and similar functions that truncate output. Same as -Wformat-truncation=1.  Same as -Wformat-truncation=.
__top_srcdir__we_CXXFLAGS += -Wformat-y2k                                   # Warn about strftime formats yielding 2-digit years.
__top_srcdir__we_CXXFLAGS += -Wformat-zero-length                           # Warn about zero-length formats.
__top_srcdir__we_CXXFLAGS += -Wframe-address                                # Warn when __builtin_frame_address or __builtin_return_address is used unsafely.
__top_srcdir__we_CXXFLAGS += -Wfree-nonheap-object                          # Warn when attempting to free a non-heap object.
__top_srcdir__we_CXXFLAGS += -Whsa                                          # Warn when a function cannot be expanded to HSAIL.
__top_srcdir__we_CXXFLAGS += -Wif-not-aligned                               # Warn when the field in a struct is not aligned.
__top_srcdir__we_CXXFLAGS += -Wignored-attributes                           # Warn whenever attributes are ignored.
__top_srcdir__we_CXXFLAGS += -Wimplicit-fallthrough                         # Same as -Wimplicit-fallthrough=3 (or, in negated form, -Wimplicit-fallthrough=0).
__top_srcdir__we_CXXFLAGS += -Winherited-variadic-ctor                      # Warn about C++11 inheriting constructors when the base has a variadic constructor.
__top_srcdir__we_CXXFLAGS += -Winit-list-lifetime                           # Warn about uses of std::initializer_list that can result in dangling pointers.
__top_srcdir__we_CXXFLAGS += -Winit-self                                    # Warn about variables which are initialized to themselves.
__top_srcdir__we_CXXFLAGS += -Winline                                       # Warn when an inlined function cannot be inlined.
__top_srcdir__we_CXXFLAGS += -Wint-in-bool-context                          # Warn for suspicious integer expressions in boolean context.
__top_srcdir__we_CXXFLAGS += -Wint-to-pointer-cast                          # Warn when there is a cast to a pointer from an integer of a different size.
__top_srcdir__we_CXXFLAGS += -Winvalid-memory-model                         # Warn when an atomic memory model parameter is known to be outside the valid range.
__top_srcdir__we_CXXFLAGS += -Winvalid-offsetof                             # Warn about invalid uses of the "offsetof" macro.
__top_srcdir__we_CXXFLAGS += -Winvalid-pch                                  # Warn about PCH files that are found but not used.
__top_srcdir__we_CXXFLAGS += -Wliteral-suffix                               # Warn when a string or character literal is followed by a ud-suffix which does not begin with an underscore.
__top_srcdir__we_CXXFLAGS += -Wlogical-not-parentheses                      # Warn when logical not is used on the left hand side operand of a comparison.
__top_srcdir__we_CXXFLAGS += -Wlogical-op                                   # Warn when a logical operator is suspiciously always evaluating to true or false.
__top_srcdir__we_CXXFLAGS += -Wlto-type-mismatch                            # During link time optimization warn about mismatched types of global declarations.
__top_srcdir__we_CXXFLAGS += -Wmemset-elt-size                              # Warn about suspicious calls to memset where the third argument contains the number of elements not multiplied by the element size.
__top_srcdir__we_CXXFLAGS += -Wmisleading-indentation                       # Warn when the indentation of the code does not reflect the block structure.
__top_srcdir__we_CXXFLAGS += -Wmismatched-tags                              # Warn when a class is redeclared or referenced using a mismatched class-key.
__top_srcdir__we_CXXFLAGS += -Wmissing-attributes                           # Warn about declarations of entities that may be missing attributes that related entities have been declared with.
__top_srcdir__we_CXXFLAGS += -Wmissing-declarations                         # Warn about global functions without previous declarations.
__top_srcdir__we_CXXFLAGS += -Wmissing-format-attribute                     # Same as -Wsuggest-attribute=format.
__top_srcdir__we_CXXFLAGS += -Wmissing-include-dirs                         # Warn about user-specified include directories that do not exist.
__top_srcdir__we_CXXFLAGS += -Wmissing-noreturn                             # Same as -Wsuggest-attribute=noreturn.
__top_srcdir__we_CXXFLAGS += -Wmissing-profile                              # Warn in case profiles in -fprofile-use do not exist.
__top_srcdir__we_CXXFLAGS += -Wmultichar                                    # Warn about use of multi-character character constants.
__top_srcdir__we_CXXFLAGS += -Wmultiple-inheritance                         # Warn on direct multiple inheritance.
__top_srcdir__we_CXXFLAGS += -Wmultistatement-macros                        # Warn about unsafe macros expanding to multiple statements used as a body of a clause such as if, else, while, switch, or for.
__top_srcdir__we_CXXFLAGS += -Wnoexcept                                     # Warn when a noexcept expression evaluates to false even though the expression can't actually throw.
__top_srcdir__we_CXXFLAGS += -Wnoexcept-type                                # Warn if C++17 noexcept function type will change the mangled name of a symbol.
__top_srcdir__we_CXXFLAGS += -Wnon-template-friend                          # Warn when non-templatized friend functions are declared within a template.
__top_srcdir__we_CXXFLAGS += -Wnon-virtual-dtor                             # Warn about non-virtual destructors.
__top_srcdir__we_CXXFLAGS += -Wnonnull-compare                              # Warn if comparing pointer parameter with nonnull attribute with NULL.
__top_srcdir__we_CXXFLAGS += -Wnormalized                                   # Same as -Wnormalized=nfc (or, in negated form, -Wnormalized=none).
__top_srcdir__we_CXXFLAGS += -Wnull-dereference                             # Warn if dereferencing a NULL pointer may lead to erroneous or undefined behavior.
__top_srcdir__we_CXXFLAGS += -Wodr                                          # Warn about some C++ One Definition Rule violations during link time optimization.
__top_srcdir__we_CXXFLAGS += -Wold-style-cast                               # Warn if a C-style cast is used in a program.
__top_srcdir__we_CXXFLAGS += -Wopenmp-simd                                  # Warn if a simd directive is overridden by the vectorizer cost model.
__top_srcdir__we_CXXFLAGS += -Woverflow                                     # Warn about overflow in arithmetic expressions.
__top_srcdir__we_CXXFLAGS += -Woverloaded-virtual                           # Warn about overloaded virtual function names.
__top_srcdir__we_CXXFLAGS += -Wpacked                                       # Warn when the packed attribute has no effect on struct layout.
__top_srcdir__we_CXXFLAGS += -Wpacked-bitfield-compat                       # Warn about packed bit-fields whose offset changed in GCC 4.4.
__top_srcdir__we_CXXFLAGS += -Wpacked-not-aligned                           # Warn when fields in a struct with the packed attribute are misaligned.
__top_srcdir__we_CXXFLAGS += -Wpedantic                                     # Issue warnings needed for strict compliance to the standard.
__top_srcdir__we_CXXFLAGS += -Wpessimizing-move                             # Warn about calling std::move on a local object in a return statement preventing copy elision.
__top_srcdir__we_CXXFLAGS += -Wplacement-new                                # Warn for placement new expressions with undefined behavior.  Same as -Wplacement-new=.
__top_srcdir__we_CXXFLAGS += -Wpmf-conversions                              # Warn when converting the type of pointers to member functions.
__top_srcdir__we_CXXFLAGS += -Wpointer-compare                              # Warn when a pointer is compared with a zero character constant.
__top_srcdir__we_CXXFLAGS += -Wpragmas                                      # Warn about misuses of pragmas.
__top_srcdir__we_CXXFLAGS += -Wprio-ctor-dtor                               # Warn if constructor or destructors with priorities from 0 to 100 are used.
__top_srcdir__we_CXXFLAGS += -Wpsabi                                        # This option lacks documentation.
__top_srcdir__we_CXXFLAGS += -Wredundant-decls                              # Warn about multiple declarations of the same object.
__top_srcdir__we_CXXFLAGS += -Wredundant-move                               # Warn about redundant calls to std::move.
__top_srcdir__we_CXXFLAGS += -Wredundant-tags                               # Warn when a class or enumerated type is referenced using a redundant class-key.
__top_srcdir__we_CXXFLAGS += -Wregister                                     # Warn about uses of register storage specifier.
__top_srcdir__we_CXXFLAGS += -Wreorder                                      # Warn when the compiler reorders code.
__top_srcdir__we_CXXFLAGS += -Wrestrict                                     # Warn when an argument passed to a restrict-qualified parameter aliases with another argument.
__top_srcdir__we_CXXFLAGS += -Wreturn-local-addr                            # Warn about returning a pointer/reference to a local or temporary variable.
__top_srcdir__we_CXXFLAGS += -Wscalar-storage-order                         # Warn on suspicious constructs involving reverse scalar storage order.
__top_srcdir__we_CXXFLAGS += -Wshadow                                       # Warn when one variable shadows another.  Same as -Wshadow=global.
__top_srcdir__we_CXXFLAGS += -Wshadow-compatible-local                      # Same as -Wshadow=compatible-local.
__top_srcdir__we_CXXFLAGS += -Wshadow-local                                 # Same as -Wshadow=local.
__top_srcdir__we_CXXFLAGS += -Wshadow=compatible-local                      # Warn when one local variable shadows another local variable or parameter of compatible type.
__top_srcdir__we_CXXFLAGS += -Wshadow=global                                # Warn when one variable shadows another (globally).  Same as -Wshadow.
__top_srcdir__we_CXXFLAGS += -Wshadow=local                                 # Warn when one local variable shadows another local variable or parameter.
__top_srcdir__we_CXXFLAGS += -Wshift-count-negative                         # Warn if shift count is negative.
__top_srcdir__we_CXXFLAGS += -Wshift-count-overflow                         # Warn if shift count >= width of type.
__top_srcdir__we_CXXFLAGS += -Wshift-negative-value                         # Warn if left shifting a negative value.
__top_srcdir__we_CXXFLAGS += -Wshift-overflow                               # Warn if left shift of a signed value overflows.  Same as -Wshift-overflow=.
__top_srcdir__we_CXXFLAGS += -Wsign-conversion                              # Warn for implicit type conversions between signed and unsigned integers.
__top_srcdir__we_CXXFLAGS += -Wsign-promo                                   # Warn when overload promotes from unsigned to signed.
__top_srcdir__we_CXXFLAGS += -Wsized-deallocation                           # Warn about missing sized deallocation functions.
__top_srcdir__we_CXXFLAGS += -Wsizeof-array-argument                        # Warn when sizeof is applied on a parameter declared as an array.
__top_srcdir__we_CXXFLAGS += -Wsizeof-pointer-div                           # Warn about suspicious divisions of two sizeof expressions that don't work correctly with pointers.
__top_srcdir__we_CXXFLAGS += -Wstack-protector                              # Warn when not issuing stack smashing protection for some reason.
__top_srcdir__we_CXXFLAGS += -Wstrict-null-sentinel                         # Warn about uncasted NULL used as sentinel.
__top_srcdir__we_CXXFLAGS += -Wstrict-overflow                              # Warn about optimizations that assume that signed overflow is undefined.
__top_srcdir__we_CXXFLAGS += -Wstring-compare                               # Warn about calls to strcmp and strncmp used in equality expressions that are necessarily true or false due to the length of one and size of the other argument.
__top_srcdir__we_CXXFLAGS += -Wstringop-overflow                            # Warn about buffer overflow in string manipulation functions like memcpy and strcpy.  Same as -Wstringop-overflow=.
__top_srcdir__we_CXXFLAGS += -Wstringop-truncation                          # Warn about truncation in string manipulation functions like strncat and strncpy.
__top_srcdir__we_CXXFLAGS += -Wsubobject-linkage                            # Warn if a class type has a base or a field whose type uses the anonymous namespace or depends on a type with no linkage.
__top_srcdir__we_CXXFLAGS += -Wsuggest-attribute=cold                       # Warn about functions which might be candidates for __attribute__((cold)).
__top_srcdir__we_CXXFLAGS += -Wsuggest-attribute=const                      # Warn about functions which might be candidates for __attribute__((const)).
__top_srcdir__we_CXXFLAGS += -Wsuggest-attribute=format                     # Warn about functions which might be candidates for format attributes.
__top_srcdir__we_CXXFLAGS += -Wsuggest-attribute=malloc                     # Warn about functions which might be candidates for __attribute__((malloc)).
__top_srcdir__we_CXXFLAGS += -Wsuggest-attribute=noreturn                   # Warn about functions which might be candidates for __attribute__((noreturn)).
__top_srcdir__we_CXXFLAGS += -Wsuggest-attribute=pure                       # Warn about functions which might be candidates for __attribute__((pure)).
__top_srcdir__we_CXXFLAGS += -Wsuggest-final-methods                        # Warn about C++ virtual methods where adding final keyword would improve code quality.
__top_srcdir__we_CXXFLAGS += -Wsuggest-final-types                          # Warn about C++ polymorphic types where adding final keyword would improve code quality.
__top_srcdir__we_CXXFLAGS += -Wsuggest-override                             # Suggest that the override keyword be used when the declaration of a virtual function overrides another.
__top_srcdir__we_CXXFLAGS += -Wswitch-bool                                  # Warn about switches with boolean controlling expression.
__top_srcdir__we_CXXFLAGS += -Wswitch-default                               # Warn about enumerated switches missing a "default:" statement.
__top_srcdir__we_CXXFLAGS += -Wswitch-outside-range                         # Warn about switch values that are outside of the switch's type range.
__top_srcdir__we_CXXFLAGS += -Wswitch-unreachable                           # Warn about statements between switch's controlling expression and the first case.
__top_srcdir__we_CXXFLAGS += -Wsync-nand                                    # Warn when __sync_fetch_and_nand and __sync_nand_and_fetch built-in functions are used.
__top_srcdir__we_CXXFLAGS += -Wtautological-compare                         # Warn if a comparison always evaluates to true or false.
__top_srcdir__we_CXXFLAGS += -Wterminate                                    # Warn if a throw expression will always result in a call to terminate().
__top_srcdir__we_CXXFLAGS += -Wtrampolines                                  # Warn whenever a trampoline is generated.
__top_srcdir__we_CXXFLAGS += -Wundef                                        # Warn if an undefined macro is used in an #if directive.
__top_srcdir__we_CXXFLAGS += -Wuninitialized                                # Warn about uninitialized automatic variables.
__top_srcdir__we_CXXFLAGS += -Wunknown-pragmas                              # Warn about unrecognized pragmas.
__top_srcdir__we_CXXFLAGS += -Wunused-const-variable                        # Warn when a const variable is unused.  Same as -Wunused-const-variable=.
__top_srcdir__we_CXXFLAGS += -Wunused-macros                                # Warn about macros defined in the main file that are not used.
__top_srcdir__we_CXXFLAGS += -Wunused-parameter                             # Warn when a function parameter is unused.
__top_srcdir__we_CXXFLAGS += -Wunused-result                                # Warn if a caller of a function, marked with attribute warn_unused_result, does not use its return value.
__top_srcdir__we_CXXFLAGS += -Wuseless-cast                                 # Warn about useless casts.
__top_srcdir__we_CXXFLAGS += -Wvarargs                                      # Warn about questionable usage of the macros used to retrieve variable arguments.
__top_srcdir__we_CXXFLAGS += -Wvector-operation-performance                 # Warn when a vector operation is compiled outside the SIMD.
__top_srcdir__we_CXXFLAGS += -Wvirtual-inheritance                          # Warn on direct virtual inheritance.
__top_srcdir__we_CXXFLAGS += -Wvirtual-move-assign                          # Warn if a virtual base has a non-trivial move assignment operator.
__top_srcdir__we_CXXFLAGS += -Wvolatile                                     # Warn about deprecated uses of volatile qualifier.
__top_srcdir__we_CXXFLAGS += -Wwrite-strings                                # In C++, nonzero means warn about deprecated conversion from string literals to 'char *'.  In C, similar warning, except that the conversion is of course not deprecated by the ISO C standard.
__top_srcdir__we_CXXFLAGS += -Wzero-as-null-pointer-constant                # Warn when a literal '0' is used as null pointer.
__top_srcdir__we_CXXFLAGS += -Wzero-length-bounds                           # Warn about accesses to interior zero-length array members.



# ___________________________________________________ Configuration __________________________________________________ #
__top_srcdir__we_CXXFLAGS += -Waligned-new=all                              # Warn even if 'new' uses a class member allocation function.
__top_srcdir__we_CXXFLAGS += -Walloc-size-larger-than=1048576               # Warn for calls to allocation functions that attempt to allocate objects larger than the specified number of bytes.
__top_srcdir__we_CXXFLAGS += -Warray-bounds=2                               # Warn if an array is accessed out of bounds.
__top_srcdir__we_CXXFLAGS += -Walloca-larger-than=4096                      # Warn on unbounded uses of alloca, and on bounded uses of alloca whose bound can be larger than <number> bytes.
__top_srcdir__we_CXXFLAGS += -Wattribute-alias=2                            # Warn about type safety and similar errors and mismatches in declarations with alias attributes.
__top_srcdir__we_CXXFLAGS += -Wcatch-value=3                                # Warn about catch handlers of non-reference type.
__top_srcdir__we_CXXFLAGS += -Wformat-overflow=2                            # Warn about function calls with format strings that write past the end of the destination region.
__top_srcdir__we_CXXFLAGS += -Wformat-truncation=2                          # Warn about calls to snprintf and similar functions that truncate output.
__top_srcdir__we_CXXFLAGS += -Wframe-larger-than=8192                       # Warn if a function's stack frame requires in excess of <byte-size>.
__top_srcdir__we_CXXFLAGS += -Wimplicit-fallthrough=5                       # Warn when a switch case falls through.
__top_srcdir__we_CXXFLAGS += -Wlarger-than=2048                             # Warn if an object's size exceeds <byte-size>.
__top_srcdir__we_CXXFLAGS += -Wformat=2                                     # Warn about printf/scanf/strftime/strfmon format string anomalies.
__top_srcdir__we_CXXFLAGS += -Wnormalized=nfc                               # Warn about non-normalized Unicode strings.
__top_srcdir__we_CXXFLAGS += -Wplacement-new=2                              # Warn for placement new expressions with undefined behavior.
__top_srcdir__we_CXXFLAGS += -Wshift-overflow=2                             # Warn if left shift of a signed value overflows.
__top_srcdir__we_CXXFLAGS += -Wstack-usage=8192                             # Warn if stack usage might exceed <byte-size>.
__top_srcdir__we_CXXFLAGS += -Wstrict-aliasing=3                            # Warn about code which might break strict aliasing rules.
__top_srcdir__we_CXXFLAGS += -Wstrict-overflow=5                            # Warn about optimizations that assume that signed overflow is undefined.
__top_srcdir__we_CXXFLAGS += -Wstringop-overflow=4                          # Under the control of Object Size type, warn about buffer overflow in string manipulation functions like memcpy and strcpy.
__top_srcdir__we_CXXFLAGS += -Wunused-const-variable=2                      # Warn when a const variable is unused.
__top_srcdir__we_CXXFLAGS += -Wvla-larger-than=0                            # Warn on unbounded uses of variable-length arrays, and on bounded uses of variable-length arrays whose bound can be larger than <number> bytes. <number> bytes.



# Advance Debug
# __top_srcdir__we_CXXFLAGS += -DDEBUG_XML
# __top_srcdir__we_CXXFLAGS += -DDEBUG_XML_FULL
# __top_srcdir__we_CXXFLAGS += -DDEBUG_PERFS


__top_srcdir__we_CXXFLAGS += ${WE_EXTRA_CXXFLAGS}               # Append user-defined flags (for instance -Wno-unknown-warning-option compiling with clang)



#  --all-warnings             This switch lacks documentation
#  --extra-warnings           This switch lacks documentation
#


#  Included in -Wall -Wextra -Wpedantic combo
#  ------------------------------------------
# -Waddress                    Warn about suspicious uses of memory addresses.
# -Warray-bounds               Warn if an array is accessed out of bounds.
# -Wchar-subscripts            Warn about subscripts whose type is "char".
# -Wclobbered                  Warn about variables that might be changed by "longjmp" or "vfork".
# -Wcomment                    Warn about possibly nested block comments, and C++ comments spanning more than one physical line.
# -Wdelete-non-virtual-dtor    Warn about deleting polymorphic objects with non-virtual destructors.
# -Wempty-body                 Warn about an empty body in an if or else statement.
# -Wenum-compare               Warn about comparison of different enum types.
# -Wformat                     Warn about printf/scanf/strftime/strfmon format string anomalies.  Same as -Wformat=.
# -Wignored-qualifiers         Warn whenever type qualifiers are ignored.
# -Wmain                       Warn about suspicious declarations of "main".
# -Wmaybe-uninitialized        Warn about maybe uninitialized automatic variables.
# -Wmemset-transposed-args     Warn about suspicious calls to memset where the third argument is constant literal zero and the second is not.
# -Wmissing-braces             Warn about possibly missing braces around initializers.
# -Wmissing-field-initializers Warn about missing fields in struct initializers.
# -Wnarrowing                  Warn about narrowing conversions within { } that are ill-formed in C++11.
# -Wnonnull                    Warn about NULL being passed to argument slots marked as requiring non-NULL.
# -Wunused-but-set-parameter   Warn when a function parameter is only set, otherwise unused.
# -Wunused-but-set-variable    Warn when a variable is only set, otherwise unused.
# -Wunused-function            Warn when a function is unused.
# -Wunused                     Enable all -Wunused- warnings.
# -Wunused-label               Warn when a label is unused.
# -Wunused-local-typedefs      Warn when typedefs locally defined in a function are not used.
# -Wunused-value               Warn when an expression value is unused.
# -Wunused-variable            Warn when a variable is unused.
# -Woverlength-strings         Warn if a string is longer than the maximum portable length specified by the standard.
# -Wparentheses                Warn about possibly missing parentheses.
# -Wpointer-arith              Warn about function pointer arithmetic.
# -Wreturn-type                Warn whenever a function's return type defaults to "int" (C), or about inconsistent return types (C++).
# -Wsequence-point             Warn about possible violations of sequence point rules.
# -Wsign-compare               Warn about signed-unsigned comparisons.
# -Wsizeof-pointer-memaccess   Warn about suspicious length parameters to certain string functions if the argument uses sizeof.
# -Wstrict-aliasing            Warn about code which might break strict aliasing rules.
# -Wswitch                     Warn about enumerated switches, with no default, missing a case.
# -Wtype-limits                Warn if a comparison is always true or always false due to the limited range of the data type.
# -Wvariadic-macros            Warn about using variadic macros.
# -Wvla                        Warn if a variable length array is used.
# -Wvolatile-register-var      Warn when a register variable is declared volatile.
# -Wtrigraphs                  Warn if trigraphs are encountered that might affect the meaning of the program.



# Note:
# -W is deprecated: use -Wextra
# -Wunreachable-code seems to have been removed
# Clang has a -Weverything not g++
# -Wnon-virtual-dtor is activated by -Weffc++ (unfortunately the latest gives too many false-positives so far)


# Deactivated warnings
# -Wsystem-headers            Do not suppress warnings from system headers
# -Waggregate-return          Warn about returning structures, unions or arrays
# -Wswitch-enum               Warn about all enumerated switches missing a specific case.
# -Weffc++                    Warn about violations of Effective C++ style rules (05/2017: too many false positives [std::string default constructor])
# -Wno-alloc-size-larger-than Disable Walloc-size-larger-than= warning.  Equivalent to Walloc-size-larger-than=<SIZE_MAX> or larger.  Same as -Walloc-size-larger-than=.
# -Wno-alloca-larger-than     Disable Walloca-larger-than= warning.  Equivalent to Walloca-larger-than=<SIZE_MAX> or larger.  Same as -Walloca-larger-than=.
# -Wno-frame-larger-than      Disable -Wframe-larger-than= warning.  Equivalent to -Wframe-larger-than=<SIZE_MAX> or larger.  Same as -Wframe-larger-than=.
# -Wno-larger-than            Disable -Wlarger-than= warning.  Equivalent to -Wlarger-than=<SIZE_MAX> or larger.  Same as -Wlarger-than=.
# -Wno-stack-usage            Disable Wstack-usage= warning.  Equivalent to Wstack-usage=<SIZE_MAX> or larger.  Same as -Wstack-usage=.
# -Wno-vla-larger-than        Disable Wvla-larger-than= warning.  Equivalent to Wvla-larger-than=<SIZE_MAX> or larger.  Same as -Wvla-larger-than=.
# -Wc++-compat                Warn about C constructs that are not in the common subset of C and C++.
# -Wc++11-compat              Warn about C++ constructs whose meaning differs between ISO C++ 1998 and ISO C++ 2011.
# -Wc++14-compat              Warn about C++ constructs whose meaning differs between ISO C++ 2011 and ISO C++ 2014.
# -Wc++17-compat              Warn about C++ constructs whose meaning differs between ISO C++ 2014 and ISO C++ 2017.
# -Wc++20-compat              Warn about C++ constructs whose meaning differs between ISO C++ 2017 and ISO C++ 2020.
# -Wc-binding-type            Warn if the type of a variable might be not interoperable with C.
# -Wc11-c2x-compat            Warn about features not present in ISO C11, but present in ISO C2X.
# -Wc90-c99-compat            Warn about features not present in ISO C90, but present in ISO C99.
# -Wc99-c11-compat            Warn about features not present in ISO C99, but present in ISO C11.
# -Wlong-long                 Do not warn about using "long long" when -pedantic. NOTE: Man page: "Warn if long long type is used...". The man is correct
# -Wtraditional               Warn about features not present in traditional C.
# -Wabi-tag                   Warn if a subobject has an abi_tag attribute that the complete object type does not have.
# -Wnamespaces                Warn about all enumerated switches missing a specific case.
# -Wtemplates                 Warn on primary template declaration.

# Deactivated warnings (unsure about the relevance in this context)
# -Wpadded                    Warn when padding is required to align structure members
# -Wstack-usage=4096          Warn if stack usage might be larger than specified amount
