# Go60 to Voyager Diff

Legend:

```text
= exact shared-position match
~ changed on Voyager to match Go60 or the chosen thumb policy
x Go60 key exists, but Voyager has no physical key there
! intentionally unsupported or unchanged
```

The diagrams use the Voyager physical subset: four 12-key rows and four thumb
keys. Go60's extra upper thumb/navigation keys are listed separately.

## Base

```text
= +        = 1       = 2       = 3       = 4       = 5          = 6       = 7       = 8       = 9       = 0       = -
~ TAB      = Q       = W       = E       = R       = T          = Y       = U       = I       = O       = P       = \
~ ESC      = A/CTL   = S/OPT   = D/CMD   = F/SFT   = G          = H       = J/SFT   = K/CMD   ~ L/OPT   = ;/CTL   = '
= Magic    = Z       = X       = C       = V       = B          = N       = M       = ,       = .       = /       ~ CapsWord
                                  ~ RET/Cursor     ~ BSPC/Symbol                    ~ _/Symbol       ~ Space/Num
```

Unmapped Go60-only base keys: `Home`, `Left`, `Right`, `Up`, `Down`, `End`.

## Cursor

```text
= TRNS     = TRNS    = TRNS    = TRNS    = TRNS    = TRNS       = TRNS    = TRNS    = TRNS    = TRNS    = TRNS     = TRNS
= TRNS     = Cmd+R   = PrevTab = NextTab ~ Cmd+[   ~ Cmd+]      = PgUp    = Home    = Up      = End     = Search   = TRNS
= TRNS     = LCTL    = LALT    = LGUI    = LSFT    = Click      = PgDn    = Left    = Down    = Right   = AreaCopy = TRNS
= TRNS     = Cmd+Z   = Redo    = Cmd+C   = Cmd+V   ~ Cmd+Sft+V  = Cmd+L   = SelBack = SelWord = SelLine = ScrCopy  = TRNS
                                  = TRNS           = TRNS                         ~ CycleTab  = LayerLock
```

Unmapped Go60-only Cursor keys: `Cmd+F`, `Cmd+Shift+G`, `Cmd+G`.

## Symbol

```text
= TRNS     = TRNS    = TRNS    = TRNS    = TRNS    = TRNS       = TRNS    = TRNS    = TRNS    = TRNS    = TRNS     = TRNS
= TRNS     = `       = <       = >       = -       = |          = ^       = {       = }       = $       = ->       = TRNS
= TRNS     = !       = *       = /       = =       = &          = #       = (       = )       = ;       = "        = TRNS
= TRNS     = ~       = +       = [       = ]       = %          = @       = :       ~ '       = .       ~ ?        = TRNS
                                  = TRNS           = TRNS                         = TRNS     = TRNS
```

Unmapped Go60-only Symbol keys: all six Go60 extra thumb/navigation positions.

## Num

```text
= ESC      = F1      = F2      = F3      = F4      = F5         = F6      = F7      = F8      = F9      = F10      = F11
= NO       = /       = 9       = 8       = 7       = *          = NO      = NO      = [       = ]       = NO       = F12
= NO       = -       = 3       = 2       = 1       = +          = NO      = RSFT    = RGUI    = RALT    = RCTL     = NO
= NO       = X       = 6       = 5       = 4       = %          = NO      = NO      = ,       = .       = NO       = NO
                                  = 0              ~ NO                           ~ LayerLock = NO
```

Unmapped Go60-only Num keys: all six Go60 extra thumb/navigation positions.

## Magic

```text
! Magic layer intentionally unchanged from the existing Voyager keymap.
```

Go60 Magic has Bluetooth, output-select, and reset behaviors that do not have a
direct shared-position QMK/ZSA equivalent in this keymap. The implementation
keeps the existing Voyager Magic layer exactly as-is.

## Mouse

```text
~ NO       ~ NO       ~ NO       ~ NO       ~ NO       ~ NO         ~ NO      ~ NO       ~ NO            ~ NO            ~ NO       ~ NO
~ MouseOff ~ Drag     ~ Scroll   ~ CPI-     ~ CPI+     ~ NO         ~ NO      ~ NO       ~ NO            ~ NO            ~ NO       ~ NO
~ ESC      ~ OSM CTL  ~ OSM ALT  ~ OSM GUI  ~ OSM SFT  ~ BackBtn    ~ NO      ~ CPI+     ~ CPI-          ~ Scroll        ~ NO       ~ NO
~ NO       ~ Cmd+Z    ~ Cmd+X    ~ Cmd+C    ~ Cmd+V    ~ FwdBtn     ~ NO      ~ NO       ~ NO            ~ NO            ~ NO       ~ NO
                                  ~ Click             ~ RightClick                    ~ LayerLock     ~ NO
```

`MouseOff` is placed at the same physical position as Base `TAB`. It uses the
Mouse layer's momentary key behavior, which exits an unlocked mouse layer and
unlocks the layer if it was layer-locked.

Go60 mouse speed/warp layers are represented by ZSA Navigator controls:
`CPI-`, `CPI+`, `Scroll`, and `Drag`.
