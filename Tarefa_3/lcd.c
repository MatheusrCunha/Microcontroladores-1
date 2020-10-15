#include "lcd.h"
#include "gpio.h"
#include "delay_wdt.h"

/**
 * @brief  Gera sinal pulso de enable por software
 * @param  Nenhum
 *
 * @retval Nenhum.
 */
static inline void enable_pulse(){
    delay_wdt(4);

    SET_BIT(PORT_OUT(LCD_CTRL_PORT),E_PIN);

    delay_wdt(4);

    CLR_BIT(PORT_OUT(LCD_CTRL_PORT),E_PIN);

    delay_wdt(4);

}

/**
 * @brief  Configura hardware: verificar lcd.h para mapa de pinos e nible de dados.
 * @param  Nenhum
 *
 * @retval Nenhum.
 */
void lcd_init_4bits()
{
    /* Configura pinos de controle */
    SET_BIT(PORT_DIR(LCD_CTRL_PORT), RS_PIN | E_PIN);

    /* Configure pinos de dados */
#if (NIBBLE_DADOS)
    PORT_DIR(LCD_DATA_PORT) |=  0xF0;
#else
    PORT_DIR(LCD_DATA_PORT) |=  0x0F;
#endif

    CLR_BIT(PORT_OUT(LCD_DATA_PORT), RS_PIN | E_PIN);
    delay_wdt(4);

    /* Interface de 8 bits */
#if (NIBBLE_DADOS)
    PORT_OUT(LCD_DATA_PORT) = (PORT_OUT(LCD_DATA_PORT) & 0x0F) | 0x30;
#else
    PORT_OUT(LCD_DATA_PORT) = (PORT_OUT(LCD_DATA_PORT) & 0xF0) | 0x03;
#endif

    enable_pulse();
    delay_wdt(4);
    enable_pulse();
    delay_wdt(4);
    enable_pulse();

#if (NIBBLE_DADOS)
    PORT_OUT(LCD_DATA_PORT) = (PORT_OUT(LCD_DATA_PORT) & 0x0F) | 0x20;
#else
    PORT_OUT(LCD_DATA_PORT) = (PORT_OUT(LCD_DATA_PORT) & 0xF0) | 0x02;
#endif

    enable_pulse();

    /* Interface de 4 bits 2 linhas
     * Mudar comando para displays maiores */
    lcd_send_data(0x28, LCD_CMD);
    lcd_send_data(LCD_TURN_OFF, LCD_CMD);
    lcd_send_data(LCD_CLEAR, LCD_CMD);

    /* Mensagem aparente e cursor inativo não piscante
     * Outros modos podem ser consultados no datasheet */
    lcd_send_data(0x0C, LCD_CMD);
    lcd_send_data(LCD_LINE_0, LCD_CMD);
}

/**
 * @brief Envia um dado estático para o display: caractere ou comando.
 * @param data: valor do comando.
 * @param data_type: LCD_CMD para comando. LCD_DATA para caractere.
 *
 * @retval Nenhum
 */
void lcd_send_data(uint8_t data, lcd_data_t data_type)
{
    //Escolha se o pino RS vai receber um comando(leitura ou escrita)
    // ou vai receber um carácter
    if (data_type == LCD_CMD)
        CLR_BIT(PORT_OUT(LCD_CTRL_PORT),RS_PIN);
    else
        SET_BIT(PORT_OUT(LCD_CTRL_PORT),RS_PIN);

    /* Envia 4 MSB primeiramente */
#if (NIBBLE_DADOS)
    PORT_OUT(LCD_DATA_PORT) = (PORT_OUT(LCD_DATA_PORT) & 0x0F)|(0xF0 & data);
#else
    PORT_OUT(LCD_DATA_PORT) = (PORT_OUT(LCD_DATA_PORT) & 0xF0) | (data >> 4);
#endif

    enable_pulse();

    /* Envia 4 LSB restantes do byte */
#if (NIBBLE_DADOS)
    PORT_OUT(LCD_DATA_PORT) = (PORT_OUT(LCD_DATA_PORT) & 0x0F) | (0xF0 & (data << 4));
#else
    PORT_OUT(LCD_DATA_PORT) = (PORT_OUT(LCD_DATA_PORT) & 0xF0) | (0x0F & data);
#endif

    enable_pulse();

    /* Delay adicional em caso de instruções lentas: limpeza, etc */
    if ( (data == 0) && ( data_type < 4))
        delay_wdt(4);// _delay_ms(2);
}

/**
  * @brief Escreve um string estática no LCD.
  * @param c: ponteiro para a string em RAM
  *
  * @retval Nenhum
  */
void lcd_write_string(unsigned char *c)
{
   for (; *c!='\0'; c++)
       lcd_send_data(*c, LCD_DATA);
}

/**
  * @brief Limpa a tela do LCD
  * @param c: Nenhum
  *
  * @retval Nenhum
  */
void lcd_clear(){
    lcd_send_data(LCD_CLEAR,LCD_CMD);
}