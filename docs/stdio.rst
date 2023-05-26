STDIO.H SUPPORT
===============


========= ============ ======= =================================================
Function  Implemented? Tested? Notes
--------- ------------ ------- -------------------------------------------------
clearerr  Y
fclose    Y                    Requires kernel support
feof      Y
ferror    Y
fopen     Y                    Requires kernel support
fprintf   ~
fread     Y                    Requires kernel support
fseek     Y                    Requires kernel support
fwrite    Y                    Requires kernel support
printf    ~
snprintf  ~
sprintf   ~
vfprintf  ~
vprintf   ~
vsnprintf ~
vsprintf  ~


The printf family of functions currently doesn't support floating-point format
specifiers.
