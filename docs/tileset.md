# Tileset

## Rabbit's tileset

### Informations

Every tiles are 32*32.

Tileset size is 480*1088.

There is 34 lines and 480 columns and 15 tiles by lines.

### Code

Clean grass : `261`

Water : `294`

Grass + Rock + Water : `279`

Left side of the beginning of a wood bridge : `280`

Right side of the beginning of a wood bridge : `281`

Left side of a wood bridge : `295`

Right side of a wood bridge : `296`

Flowers 1 : `276`

Flowers 2 : `291`

Vertical road : `262`

Horizontal road : `292`

Multiple access road : `277`

Horizontal top fence : `400`

Horizontal bottom fence : `430`

Vertical fence : `414`

Top left corner fence : `399`

Top Right corner fence : `401`

Bottom left corner fence : `429`

Bottom right corner fence : `431`

By this way, here is the code to make an area closed by fences (29 is void) :
    
    399, 400, 400, 401
    414,  29,  29, 414
    429, 430, 430, 431

House with yellow roof and a fireplace :
    
    375, 376, 377, 378
    390, 391, 392, 393
    405, 406, 407, 408
    420, 421, 422, 423

Small bush :
    
    272, 273
    287, 288

Big bush :
    
    270, 271
    285, 286
