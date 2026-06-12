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
  --layer-names Base Symbols Nav Num Magic \
  -b docs/keymap.yaml \
  -q "$tmp_json" \
  -o "$tmp_yaml"

perl -0pi -e 's/layout_name: LAYOUT_voyager/layout_name: LAYOUT/' "$tmp_yaml"
perl -0pi -e "s/ESCAPE/ESC/g; s/LEFT CTRL/LCTL/g; s/RIGHT GUI/RGUI/g; s/{t: CTL A, h: CTL}/{t: A, h: CTL}/g; s/{t: OPT S, h: OPT}/{t: S, h: OPT}/g; s/{t: CMD D, h: CMD}/{t: D, h: CMD}/g; s/{t: SFT F, h: SFT}/{t: F, h: SFT}/g; s/{t: SFT J, h: SFT}/{t: J, h: SFT}/g; s/{t: CMD K, h: CMD}/{t: K, h: CMD}/g; s/{t: OPT L, h: OPT}/{t: L, h: OPT}/g; s/{t: CTL SCLN, h: CTL}/{t: ';', h: CTL}/g" "$tmp_yaml"
perl -0pi -e "s/{t: UND NAV, h: Nav}/{t: '_', h: Nav}/g; s/UND NAV/'_'/g; s/{t: F19, h: Nav}/{t: '_', h: Nav}/g; s/{t: SPACE, h: Media}/SPACE/g; s/{t: '~', type: trans}/'~'/g; s/ARROW/'->'/g" "$tmp_yaml"
perl -0pi -e "s/{t: ▽, h: MOD_LCTL, type: trans}/{t: ▽, type: trans}/g; s/{t: Gui\\+R, type: trans}/Cmd+R/g; s/Gui\\+R/Cmd+R/g; s/Ctl\\+Sft\\+TAB/Prev Tab/g; s/Ctl\\+TAB/Next Tab/g; s/WBAK/Back/g; s/{t: WFWD, type: trans}/Forward/g; s/WFWD/Forward/g; s/{t: SRCHSEL, type: trans}/Search Sel/g; s/SRCHSEL/Search Sel/g; s/{t: DEL, type: trans}/DEL/g; s/{t: Gui\\+Z, type: trans}/Cmd+Z/g; s/Gui\\+Z/Cmd+Z/g; s/{t: Gui\\+X, type: trans}/Cmd+X/g; s/Gui\\+X/Cmd+X/g; s/Gui\\+C/Cmd+C/g; s/Gui\\+V/Cmd+V/g; s/SELBack/Sel Word Back/g; s/SELWBAK/Sel Word Back/g; s/SELWORD/Sel Word/g; s/{t: SELLINE, type: trans}/Sel Line/g; s/SELLINE/Sel Line/g; s/{t: Gui\\+TAB, type: trans}/Cmd+Tab/g; s/Gui\\+TAB/Cmd+Tab/g; s/{t: QK LLCK, type: trans}/Layer Lock/g; s/QK LLCK/Layer Lock/g" "$tmp_yaml"
perl -0pi -e "s/{t: '\\|', type: trans}/'|'/g; s/{t: \\^, type: trans}/^/g; s/{t: '&', type: trans}/'&'/g; s/{t: '#', type: trans}/'#'/g; s/{t: \\+, type: trans}/+/g; s/{t: '\\[', type: trans}/'['/g; s/{t: '\\]', type: trans}/']'/g; s/{t: '%', type: trans}/'%'/g; s/{t: '@', type: trans}/'@'/g; s/{t: ':', type: trans}/':'/g; s/{t: ',', type: trans}/','/g; s/{t: \\., type: trans}/./g; s/{t: '''', type: trans}/''''/g" "$tmp_yaml"
perl -0pi -e "s/\{t: '\@', type: trans\}/'\@'/g" "$tmp_yaml"
cp "$tmp_yaml" docs/keymap.yaml
keymap draw docs/keymap.yaml -o docs/keymap.svg
