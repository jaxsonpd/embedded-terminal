add_executable(embedded-terminal main.c clear.c "command.c" help.c IO.c led.c utils.c)

target_compile_options(embedded-terminal PRIVATE -Os -DF_CPU=16000000UL -mmcu=atmega328p -Wall -Wstrict-prototypes -Wextra)
target_link_libraries(embedded-terminal PRIVATE avr-extends)