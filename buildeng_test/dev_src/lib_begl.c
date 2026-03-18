#if defined(__has_include)
#  if __has_include("main.c")
#    error "totally expected compilation failure: 0xBEEFBEEF"
#  endif
#endif

const char *lib_begl(void) {
    return "QSBkZWxpZ2h0ZnVsIHN1cnByaXNlLCB0aGlz";
}