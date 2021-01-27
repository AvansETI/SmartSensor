#ifndef _STD_UTIL_H_
#define	_STD_UTIL_H_

#define  util_GetBitMask(bit)          (1<<(bit))
#define  util_BitSet(x,bit)            ((x) |=  util_GetBitMask(bit))
#define  util_BitClear(x,bit)          ((x) &= ~util_GetBitMask(bit))
#define  util_BitToggle(x,bit)         ((x) ^=  util_GetBitMask(bit))
#define  util_UpdateBit(x,bit,val)     ((val)? util_BitSet(x,bit): util_BitClear(x,bit))
#define  util_GetBitStatus(x,bit)      (((x)&(util_GetBitMask(bit)))!=0u)

#define util_GetMod8(dividend,divisor)  (uint8_t) (dividend - (divisor * (uint8_t) (dividend/divisor)))
#define util_GetMod16(dividend,divisor) (uint16_t)(dividend - (divisor * (uint16_t)(dividend/divisor)))
#define util_GetMod32(dividend,divisor) (uint32_t)(dividend - (divisor * (uint32_t)(dividend/divisor)))

#define util_Dec2Ascii(Dec)	 ((Dec)+0x30)
#define util_Ascii2Dec(Asc)	 ((Asc)-0x30)
#define util_Hex2Ascii(Hex)  (((Hex)>0x09) ? ((Hex) + 0x37): ((Hex) + 0x30))
#define util_Ascii2Hex(Asc)  (((Asc)>0x39) ? ((Asc) - 0x37): ((Asc) - 0x30))

#endif // _STD_UTIL_H_