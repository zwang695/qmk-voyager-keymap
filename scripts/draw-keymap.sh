#!/usr/bin/env bash
set -euo pipefail

export PATH="$HOME/.local/bin:/root/.local/bin:/home/zacha/.local/bin:$PATH"

tmp_json="$(mktemp)"
tmp_yaml="$(mktemp)"
cleanup() {
  rm -f "$tmp_json" "$tmp_yaml"
}
trap cleanup EXIT

qmk c2json --no-cpp \
  -kb zsa/voyager \
  -km zwang695 \
  keyboards/zsa/voyager/keymaps/zwang695/keymap.c \
  -o "$tmp_json"

keymap parse \
  -c 12 \
  --layer-names Base Symbols Media \
  -b docs/keymap.yaml \
  -q "$tmp_json" \
  -o "$tmp_yaml"

perl -0pi -e 's/layout_name: LAYOUT_voyager/layout_name: LAYOUT/' "$tmp_yaml"
perl -0pi -e "s/ESCAPE/ESC/g; s/LEFT CTRL/LCTL/g; s/RIGHT GUI/RGUI/g; s/{t: CTL A, h: CTL}/{t: A, h: CTL}/g; s/{t: OPT S, h: OPT}/{t: S, h: OPT}/g; s/{t: CMD D, h: CMD}/{t: D, h: CMD}/g; s/{t: SFT F, h: SFT}/{t: F, h: SFT}/g; s/{t: SFT J, h: SFT}/{t: J, h: SFT}/g; s/{t: CMD K, h: CMD}/{t: K, h: CMD}/g; s/{t: OPT L, h: OPT}/{t: L, h: OPT}/g; s/{t: CTL SCLN, h: CTL}/{t: ';', h: CTL}/g" "$tmp_yaml"
perl -0pi -e "s/{t: ENTER, h: Symbols}/ENTER/g; s/{t: '~', type: trans}/'~'/g; s/ARROW/'->'/g" "$tmp_yaml"
cp "$tmp_yaml" docs/keymap.yaml
keymap draw docs/keymap.yaml -o docs/keymap.svg
