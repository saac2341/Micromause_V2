/*Libreria encargada de la comunicacion entre el micromouse y la computadora, permitiendo enviar datos de los sensores y recibir comandos para controlar el micromouse.*/
#include "comunicacion.h"
#include "temp/default.h"

void setup_uart(void) {
    // Implementation for setting up UART
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
}