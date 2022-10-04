bin_PROGRAMS = $(top_srcdir)/we

# Link against pugixml
__top_srcdir__we_LDADD  = ${abs_top_builddir}/lib/libpugixml.a
__top_srcdir__we_LDADD += -lstdc++fs # filesystem

__top_srcdir__we_CXXFLAGS = -I${abs_top_builddir}/lib/

# Different main() if testing or not
if UNIT_TESTS
  __top_srcdir__we_SOURCES = ${abs_top_builddir}/tests/unit/main.cc
#  __top_srcdir__we_CXXFLAGS += -I${abs_top_builddir}/tests/unit/lib/
else
  __top_srcdir__we_SOURCES = main.cc
endif


# Source files
common_sources =                         \
\
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
common_sources +=          \
  generated/enum_print/enum_print.cc

__top_srcdir__we_SOURCES += ${common_sources}


# ____________________________________ Compiler configuration ____________________________________ #
release_flags = -s -O3 -DNDEBUG -Wno-inline # -Ofast
debug_flags = -O0 -g3 -ggdb3 -DDEBUG # -Og: not clang compliant
__top_srcdir__we_CXXFLAGS += ${debug_flags}

# export GLIBCXX_FORCE_NEW

common_warnings  = -Waddress-of-packed-member                     # Warn when the address of packed member of struct or union is taken.
common_warnings += -Waggressive-loop-optimizations                # Warn if a loop with constant number of iterations triggers undefined behavior.
common_warnings += -Wall                                          # Enable most warning messages.
common_warnings += -Walloc-zero                                   # Warn for calls to allocation functions that specify zero bytes.
common_warnings += -Walloca                                       # Warn on any use of alloca.
common_warnings += -Wanalyzer-double-fclose                       # Warn about code paths in which a stdio FILE can be closed more than once.
common_warnings += -Wanalyzer-double-free                         # Warn about code paths in which a pointer can be freed more than once.
common_warnings += -Wanalyzer-exposure-through-output-file        # Warn about code paths in which sensitive data is written to a file.
common_warnings += -Wanalyzer-file-leak                           # Warn about code paths in which a stdio FILE is not closed.
common_warnings += -Wanalyzer-free-of-non-heap                    # Warn about code paths in which a non-heap pointer is freed.
common_warnings += -Wanalyzer-malloc-leak                         # Warn about code paths in which a heap-allocated pointer leaks.
common_warnings += -Wanalyzer-null-argument                       # Warn about code paths in which NULL is passed to a must-not-be-NULL function argument.
common_warnings += -Wanalyzer-null-dereference                    # Warn about code paths in which a NULL pointer is dereferenced.
common_warnings += -Wanalyzer-possible-null-argument              # Warn about code paths in which a possibly-NULL value is passed to a must-not-be-NULL function argument.
common_warnings += -Wanalyzer-possible-null-dereference           # Warn about code paths in which a possibly-NULL pointer is dereferenced.
common_warnings += -Wanalyzer-stale-setjmp-buffer                 # Warn about code paths in which a longjmp rewinds to a jmp_buf saved in a stack frame that has returned.
common_warnings += -Wanalyzer-tainted-array-index                 # Warn about code paths in which an unsanitized value is used as an array index.
common_warnings += -Wanalyzer-too-complex                         # Warn if the code is too complicated for the analyzer to fully explore.
common_warnings += -Wanalyzer-unsafe-call-within-signal-handler   # Warn about code paths in which an async-signal-unsafe function is called from a signal handler.
common_warnings += -Wanalyzer-use-after-free                      # Warn about code paths in which a freed value is used.
common_warnings += -Wanalyzer-use-of-pointer-in-stale-stack-frame # Warn about code paths in which a pointer to a stale stack frame is used.
common_warnings += -Warith-conversion                             # Warn if conversion of the result of arithmetic might change the value even though converting the operands cannot.
common_warnings += -Wattribute-alias                              # Warn about type safety and similar errors and mismatches in declarations with alias attributes.  Same as -Wattribute-alias=.
common_warnings += -Wattribute-warning                            # Warn about uses of __attribute__((warning)) declarations.
common_warnings += -Wattributes                                   # Warn about inappropriate attribute usage.
common_warnings += -Wbool-compare                                 # Warn about boolean expression compared with an integer value different from true/false.
common_warnings += -Wbool-operation                               # Warn about certain operations on boolean expressions.
common_warnings += -Wbuiltin-declaration-mismatch                 # Warn when a built-in function is declared with the wrong signature.
common_warnings += -Wbuiltin-macro-redefined                      # Warn when a built-in preprocessor macro is undefined or redefined.
common_warnings += -Wcannot-profile                               # Warn when profiling instrumentation was requested, but could not be applied to a certain function.
common_warnings += -Wcast-align                                   # Warn about pointer casts which increase alignment.
common_warnings += -Wcast-align=strict                            # Warn about pointer casts which increase alignment.
common_warnings += -Wcast-function-type                           # Warn about casts between incompatible function types.
common_warnings += -Wcast-qual                                    # Warn about casts which discard qualifiers.
common_warnings += -Wcatch-value                                  # Warn about catch handlers of non-reference type.  Same as -Wcatch-value=.
common_warnings += -Wclass-conversion                             # Warn when a conversion function will never be called due to the type it converts to.
common_warnings += -Wclass-memaccess                              # Warn for unsafe raw memory writes to objects of class types.
common_warnings += -Wcomma-subscript                              # Warn about uses of a comma operator within a subscripting expression.
common_warnings += -Wcomments                                     # Synonym for -Wcomment.  Same as -Wcomment.
common_warnings += -Wconditionally-supported                      # Warn for conditionally-supported constructs.
common_warnings += -Wconversion                                   # Warn for implicit type conversions that may change a value.
common_warnings += -Wconversion-null                              # Warn for converting NULL from/to a non-pointer type.
common_warnings += -Wcoverage-mismatch                            # Warn in case profiles in -fprofile-use do not match.
common_warnings += -Wcpp                                          # Warn when a #warning directive is encountered.
common_warnings += -Wctor-dtor-privacy                            # Warn when all constructors and destructors are private.
common_warnings += -Wdangling-else                                # Warn about dangling else.
common_warnings += -Wdate-time                                    # Warn about __TIME__, __DATE__ and __TIMESTAMP__ usage.
common_warnings += -Wdelete-incomplete                            # Warn when deleting a pointer to incomplete type.
common_warnings += -Wdeprecated                                   # Warn if a deprecated compiler feature, class, method, or field is used.
common_warnings += -Wdeprecated-copy                              # Mark implicitly-declared copy operations as deprecated if the class has a user-provided copy operation.
common_warnings += -Wdeprecated-copy-dtor                         # Mark implicitly-declared copy operations as deprecated if the class has a user-provided copy operation or destructor.
common_warnings += -Wdeprecated-declarations                      # Warn about uses of __attribute__((deprecated)) declarations.
common_warnings += -Wdisabled-optimization                        # Warn when an optimization pass is disabled.
common_warnings += -Wdiv-by-zero                                  # Warn about compile-time integer division by zero.
common_warnings += -Wdouble-promotion                             # Warn about implicit conversions from "float" to "double".
common_warnings += -Wduplicated-branches                          # Warn about duplicated branches in if-else statements.
common_warnings += -Wduplicated-cond                              # Warn about duplicated conditions in an if-else-if chain.
common_warnings += -Wendif-labels                                 # Warn about stray tokens after #else and #endif.
common_warnings += -Wexpansion-to-defined                         # Warn if "defined" is used outside #if.
common_warnings += -Wextra                                        # Print extra (possibly unwanted) warnings.
common_warnings += -Wextra-semi                                   # Warn about semicolon after in-class function definition.
common_warnings += -Wfloat-conversion                             # Warn for implicit type conversions that cause loss of floating point precision.
common_warnings += -Wfloat-equal                                  # Warn if testing floating point numbers for equality.
common_warnings += -Wformat-contains-nul                          # Warn about format strings that contain NUL bytes.
common_warnings += -Wformat-diag                                  # Warn about GCC format strings with strings unsuitable for diagnostics.
common_warnings += -Wformat-extra-args                            # Warn if passing too many arguments to a function for its format string.
common_warnings += -Wformat-nonliteral                            # Warn about format strings that are not literals.
common_warnings += -Wformat-security                              # Warn about possible security problems with format functions.
common_warnings += -Wformat-signedness                            # Warn about sign differences with format functions.
common_warnings += -Wformat-truncation                            # Warn about calls to snprintf and similar functions that truncate output. Same as -Wformat-truncation=1.  Same as -Wformat-truncation=.
common_warnings += -Wformat-y2k                                   # Warn about strftime formats yielding 2-digit years.
common_warnings += -Wformat-zero-length                           # Warn about zero-length formats.
common_warnings += -Wframe-address                                # Warn when __builtin_frame_address or __builtin_return_address is used unsafely.
common_warnings += -Wfree-nonheap-object                          # Warn when attempting to free a non-heap object.
common_warnings += -Whsa                                          # Warn when a function cannot be expanded to HSAIL.
common_warnings += -Wif-not-aligned                               # Warn when the field in a struct is not aligned.
common_warnings += -Wignored-attributes                           # Warn whenever attributes are ignored.
common_warnings += -Wimplicit-fallthrough                         # Same as -Wimplicit-fallthrough=3 (or, in negated form, -Wimplicit-fallthrough=0).
common_warnings += -Winherited-variadic-ctor                      # Warn about C++11 inheriting constructors when the base has a variadic constructor.
common_warnings += -Winit-list-lifetime                           # Warn about uses of std::initializer_list that can result in dangling pointers.
common_warnings += -Winit-self                                    # Warn about variables which are initialized to themselves.
common_warnings += -Winline                                       # Warn when an inlined function cannot be inlined.
common_warnings += -Wint-in-bool-context                          # Warn for suspicious integer expressions in boolean context.
common_warnings += -Wint-to-pointer-cast                          # Warn when there is a cast to a pointer from an integer of a different size.
common_warnings += -Winvalid-memory-model                         # Warn when an atomic memory model parameter is known to be outside the valid range.
common_warnings += -Winvalid-offsetof                             # Warn about invalid uses of the "offsetof" macro.
common_warnings += -Winvalid-pch                                  # Warn about PCH files that are found but not used.
common_warnings += -Wliteral-suffix                               # Warn when a string or character literal is followed by a ud-suffix which does not begin with an underscore.
common_warnings += -Wlogical-not-parentheses                      # Warn when logical not is used on the left hand side operand of a comparison.
common_warnings += -Wlogical-op                                   # Warn when a logical operator is suspiciously always evaluating to true or false.
common_warnings += -Wlto-type-mismatch                            # During link time optimization warn about mismatched types of global declarations.
common_warnings += -Wmemset-elt-size                              # Warn about suspicious calls to memset where the third argument contains the number of elements not multiplied by the element size.
common_warnings += -Wmisleading-indentation                       # Warn when the indentation of the code does not reflect the block structure.
common_warnings += -Wmismatched-tags                              # Warn when a class is redeclared or referenced using a mismatched class-key.
common_warnings += -Wmissing-attributes                           # Warn about declarations of entities that may be missing attributes that related entities have been declared with.
common_warnings += -Wmissing-declarations                         # Warn about global functions without previous declarations.
common_warnings += -Wmissing-format-attribute                     # Same as -Wsuggest-attribute=format.
common_warnings += -Wmissing-include-dirs                         # Warn about user-specified include directories that do not exist.
common_warnings += -Wmissing-noreturn                             # Same as -Wsuggest-attribute=noreturn.
common_warnings += -Wmissing-profile                              # Warn in case profiles in -fprofile-use do not exist.
common_warnings += -Wmultichar                                    # Warn about use of multi-character character constants.
common_warnings += -Wmultiple-inheritance                         # Warn on direct multiple inheritance.
common_warnings += -Wmultistatement-macros                        # Warn about unsafe macros expanding to multiple statements used as a body of a clause such as if, else, while, switch, or for.
common_warnings += -Wnoexcept                                     # Warn when a noexcept expression evaluates to false even though the expression can't actually throw.
common_warnings += -Wnoexcept-type                                # Warn if C++17 noexcept function type will change the mangled name of a symbol.
common_warnings += -Wnon-template-friend                          # Warn when non-templatized friend functions are declared within a template.
common_warnings += -Wnon-virtual-dtor                             # Warn about non-virtual destructors.
common_warnings += -Wnonnull-compare                              # Warn if comparing pointer parameter with nonnull attribute with NULL.
common_warnings += -Wnormalized                                   # Same as -Wnormalized=nfc (or, in negated form, -Wnormalized=none).
common_warnings += -Wnull-dereference                             # Warn if dereferencing a NULL pointer may lead to erroneous or undefined behavior.
common_warnings += -Wodr                                          # Warn about some C++ One Definition Rule violations during link time optimization.
common_warnings += -Wold-style-cast                               # Warn if a C-style cast is used in a program.
common_warnings += -Wopenmp-simd                                  # Warn if a simd directive is overridden by the vectorizer cost model.
common_warnings += -Woverflow                                     # Warn about overflow in arithmetic expressions.
common_warnings += -Woverloaded-virtual                           # Warn about overloaded virtual function names.
common_warnings += -Wpacked                                       # Warn when the packed attribute has no effect on struct layout.
common_warnings += -Wpacked-bitfield-compat                       # Warn about packed bit-fields whose offset changed in GCC 4.4.
common_warnings += -Wpacked-not-aligned                           # Warn when fields in a struct with the packed attribute are misaligned.
common_warnings += -Wpedantic                                     # Issue warnings needed for strict compliance to the standard.
common_warnings += -Wpessimizing-move                             # Warn about calling std::move on a local object in a return statement preventing copy elision.
common_warnings += -Wplacement-new                                # Warn for placement new expressions with undefined behavior.  Same as -Wplacement-new=.
common_warnings += -Wpmf-conversions                              # Warn when converting the type of pointers to member functions.
common_warnings += -Wpointer-compare                              # Warn when a pointer is compared with a zero character constant.
common_warnings += -Wpragmas                                      # Warn about misuses of pragmas.
common_warnings += -Wprio-ctor-dtor                               # Warn if constructor or destructors with priorities from 0 to 100 are used.
common_warnings += -Wpsabi                                        # This option lacks documentation.
common_warnings += -Wredundant-decls                              # Warn about multiple declarations of the same object.
common_warnings += -Wredundant-move                               # Warn about redundant calls to std::move.
common_warnings += -Wredundant-tags                               # Warn when a class or enumerated type is referenced using a redundant class-key.
common_warnings += -Wregister                                     # Warn about uses of register storage specifier.
common_warnings += -Wreorder                                      # Warn when the compiler reorders code.
common_warnings += -Wrestrict                                     # Warn when an argument passed to a restrict-qualified parameter aliases with another argument.
common_warnings += -Wreturn-local-addr                            # Warn about returning a pointer/reference to a local or temporary variable.
common_warnings += -Wscalar-storage-order                         # Warn on suspicious constructs involving reverse scalar storage order.
common_warnings += -Wshadow                                       # Warn when one variable shadows another.  Same as -Wshadow=global.
common_warnings += -Wshadow-compatible-local                      # Same as -Wshadow=compatible-local.
common_warnings += -Wshadow-local                                 # Same as -Wshadow=local.
common_warnings += -Wshadow=compatible-local                      # Warn when one local variable shadows another local variable or parameter of compatible type.
common_warnings += -Wshadow=global                                # Warn when one variable shadows another (globally).  Same as -Wshadow.
common_warnings += -Wshadow=local                                 # Warn when one local variable shadows another local variable or parameter.
common_warnings += -Wshift-count-negative                         # Warn if shift count is negative.
common_warnings += -Wshift-count-overflow                         # Warn if shift count >= width of type.
common_warnings += -Wshift-negative-value                         # Warn if left shifting a negative value.
common_warnings += -Wshift-overflow                               # Warn if left shift of a signed value overflows.  Same as -Wshift-overflow=.
common_warnings += -Wsign-conversion                              # Warn for implicit type conversions between signed and unsigned integers.
common_warnings += -Wsign-promo                                   # Warn when overload promotes from unsigned to signed.
common_warnings += -Wsized-deallocation                           # Warn about missing sized deallocation functions.
common_warnings += -Wsizeof-array-argument                        # Warn when sizeof is applied on a parameter declared as an array.
common_warnings += -Wsizeof-pointer-div                           # Warn about suspicious divisions of two sizeof expressions that don't work correctly with pointers.
common_warnings += -Wstack-protector                              # Warn when not issuing stack smashing protection for some reason.
common_warnings += -Wstrict-null-sentinel                         # Warn about uncasted NULL used as sentinel.
common_warnings += -Wstrict-overflow                              # Warn about optimizations that assume that signed overflow is undefined.
common_warnings += -Wstring-compare                               # Warn about calls to strcmp and strncmp used in equality expressions that are necessarily true or false due to the length of one and size of the other argument.
common_warnings += -Wstringop-overflow                            # Warn about buffer overflow in string manipulation functions like memcpy and strcpy.  Same as -Wstringop-overflow=.
common_warnings += -Wstringop-truncation                          # Warn about truncation in string manipulation functions like strncat and strncpy.
common_warnings += -Wsubobject-linkage                            # Warn if a class type has a base or a field whose type uses the anonymous namespace or depends on a type with no linkage.
common_warnings += -Wsuggest-attribute=cold                       # Warn about functions which might be candidates for __attribute__((cold)).
common_warnings += -Wsuggest-attribute=const                      # Warn about functions which might be candidates for __attribute__((const)).
common_warnings += -Wsuggest-attribute=format                     # Warn about functions which might be candidates for format attributes.
common_warnings += -Wsuggest-attribute=malloc                     # Warn about functions which might be candidates for __attribute__((malloc)).
common_warnings += -Wsuggest-attribute=noreturn                   # Warn about functions which might be candidates for __attribute__((noreturn)).
common_warnings += -Wsuggest-attribute=pure                       # Warn about functions which might be candidates for __attribute__((pure)).
common_warnings += -Wsuggest-final-methods                        # Warn about C++ virtual methods where adding final keyword would improve code quality.
common_warnings += -Wsuggest-final-types                          # Warn about C++ polymorphic types where adding final keyword would improve code quality.
common_warnings += -Wsuggest-override                             # Suggest that the override keyword be used when the declaration of a virtual function overrides another.
common_warnings += -Wswitch-bool                                  # Warn about switches with boolean controlling expression.
common_warnings += -Wswitch-default                               # Warn about enumerated switches missing a "default:" statement.
common_warnings += -Wswitch-outside-range                         # Warn about switch values that are outside of the switch's type range.
common_warnings += -Wswitch-unreachable                           # Warn about statements between switch's controlling expression and the first case.
common_warnings += -Wsync-nand                                    # Warn when __sync_fetch_and_nand and __sync_nand_and_fetch built-in functions are used.
common_warnings += -Wtautological-compare                         # Warn if a comparison always evaluates to true or false.
common_warnings += -Wterminate                                    # Warn if a throw expression will always result in a call to terminate().
common_warnings += -Wtrampolines                                  # Warn whenever a trampoline is generated.
common_warnings += -Wundef                                        # Warn if an undefined macro is used in an #if directive.
common_warnings += -Wuninitialized                                # Warn about uninitialized automatic variables.
common_warnings += -Wunknown-pragmas                              # Warn about unrecognized pragmas.
common_warnings += -Wunused-const-variable                        # Warn when a const variable is unused.  Same as -Wunused-const-variable=.
common_warnings += -Wunused-macros                                # Warn about macros defined in the main file that are not used.
common_warnings += -Wunused-parameter                             # Warn when a function parameter is unused.
common_warnings += -Wunused-result                                # Warn if a caller of a function, marked with attribute warn_unused_result, does not use its return value.
common_warnings += -Wuseless-cast                                 # Warn about useless casts.
common_warnings += -Wvarargs                                      # Warn about questionable usage of the macros used to retrieve variable arguments.
common_warnings += -Wvector-operation-performance                 # Warn when a vector operation is compiled outside the SIMD.
common_warnings += -Wvirtual-inheritance                          # Warn on direct virtual inheritance.
common_warnings += -Wvirtual-move-assign                          # Warn if a virtual base has a non-trivial move assignment operator.
common_warnings += -Wvolatile                                     # Warn about deprecated uses of volatile qualifier.
common_warnings += -Wwrite-strings                                # In C++, nonzero means warn about deprecated conversion from string literals to 'char *'.  In C, similar warning, except that the conversion is of course not deprecated by the ISO C standard.
common_warnings += -Wzero-as-null-pointer-constant                # Warn when a literal '0' is used as null pointer.
common_warnings += -Wzero-length-bounds                           # Warn about accesses to interior zero-length array members.



# --------------------------------------------------- Configuration -------------------------------------------------- #
common_warnings += -Waligned-new=all                              # Warn even if 'new' uses a class member allocation function.
common_warnings += -Walloc-size-larger-than=1048576               # Warn for calls to allocation functions that attempt to allocate objects larger than the specified number of bytes.
common_warnings += -Warray-bounds=2                               # Warn if an array is accessed out of bounds.
common_warnings += -Walloca-larger-than=4096                      # Warn on unbounded uses of alloca, and on bounded uses of alloca whose bound can be larger than <number> bytes.
common_warnings += -Wattribute-alias=2                            # Warn about type safety and similar errors and mismatches in declarations with alias attributes.
common_warnings += -Wcatch-value=3                                # Warn about catch handlers of non-reference type.
common_warnings += -Wformat-overflow=2                            # Warn about function calls with format strings that write past the end of the destination region.
common_warnings += -Wformat-truncation=2                          # Warn about calls to snprintf and similar functions that truncate output.
common_warnings += -Wframe-larger-than=8192                       # Warn if a function's stack frame requires in excess of <byte-size>.
common_warnings += -Wimplicit-fallthrough=5                       # Warn when a switch case falls through.
common_warnings += -Wlarger-than=2048                             # Warn if an object's size exceeds <byte-size>.
common_warnings += -Wformat=2                                     # Warn about printf/scanf/strftime/strfmon format string anomalies.
common_warnings += -Wnormalized=nfc                               # Warn about non-normalized Unicode strings.
common_warnings += -Wplacement-new=2                              # Warn for placement new expressions with undefined behavior.
common_warnings += -Wshift-overflow=2                             # Warn if left shift of a signed value overflows.
common_warnings += -Wstack-usage=8192                             # Warn if stack usage might exceed <byte-size>.
common_warnings += -Wstrict-aliasing=3                            # Warn about code which might break strict aliasing rules.
common_warnings += -Wstrict-overflow=5                            # Warn about optimizations that assume that signed overflow is undefined.
common_warnings += -Wstringop-overflow=4                          # Under the control of Object Size type, warn about buffer overflow in string manipulation functions like memcpy and strcpy.
common_warnings += -Wunused-const-variable=2                      # Warn when a const variable is unused.
common_warnings += -Wvla-larger-than=0                            # Warn on unbounded uses of variable-length arrays, and on bounded uses of variable-length arrays whose bound can be larger than <number> bytes. <number> bytes.

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



# Advance Debug (custom macros)
# common_warnings += -DDEBUG_LEAKS
# common_warnings += -DDEBUG_XML
# common_warnings += -DDEBUG_XML_FULL
# common_warnings += -DDEBUG_PERFS

__top_srcdir__we_CXXFLAGS += ${common_warnings}
__top_srcdir__we_CXXFLAGS += ${WE_EXTRA_CXXFLAGS} # Append user-defined flags (for instance -Wno-unknown-warning-option compiling with clang)



# ___________________________________________ Unit Tests _________________________________________ #
# It would probably be better to separate unit tests build, for instance in tests/unit/Makefile.am
# So far, I cannot properly handle SUBDIRS without copy-pasting the sources / compilation flags
#SUBDIRS = ../tests/unit/
check_PROGRAMS = ${top_srcdir}/unit_tests_suite
TESTS = ${check_PROGRAMS} # Bind with `make check`

__top_srcdir__unit_tests_suite_LDADD = ${__top_srcdir__we_LDADD}

__top_srcdir__unit_tests_suite_CXXFLAGS  = -I${abs_top_builddir}/../tests/unit/ -I ${abs_top_builddir}/lib/ -I${srcdir}/../tests/unit/lib/
__top_srcdir__unit_tests_suite_CXXFLAGS += ${common_warnings}
__top_srcdir__unit_tests_suite_CXXFLAGS += ${WE_EXTRA_CXXFLAGS}

__top_srcdir__unit_tests_suite_SOURCES =   \
  ${common_sources}                        \
  ${top_builddir}/tests/unit/lib/doctest.h \
  ${top_builddir}/tests/unit/main.cc
