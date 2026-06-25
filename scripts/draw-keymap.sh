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
  --layer-names Base Symbol Cursor Num Magic Mouse \
  -q "$tmp_json" \
  -o "$tmp_yaml"

perl -0pi -e 's/layout_name: LAYOUT_voyager/layout_name: LAYOUT/' "$tmp_yaml"
perl -0pi -e "s/ESCAPE/ESC/g; s/LEFT CTRL/LCTL/g; s/RIGHT GUI/RGUI/g; s/{t: CTL A, h: CTL}/{t: A, h: CTL}/g; s/CTL A/{t: A, h: CTL}/g; s/{t: OPT S, h: OPT}/{t: S, h: OPT}/g; s/OPT S/{t: S, h: OPT}/g; s/{t: CMD D, h: CMD}/{t: D, h: CMD}/g; s/CMD D/{t: D, h: CMD}/g; s/{t: SFT F, h: SFT}/{t: F, h: SFT}/g; s/SFT F/{t: F, h: SFT}/g; s/{t: SFT J, h: SFT}/{t: J, h: SFT}/g; s/SFT J/{t: J, h: SFT}/g; s/{t: CMD K, h: CMD}/{t: K, h: CMD}/g; s/CMD K/{t: K, h: CMD}/g; s/{t: OPT L, h: OPT}/{t: L, h: OPT}/g; s/OPT L/{t: L, h: OPT}/g; s/{t: CTL SCLN, h: CTL}/{t: ';', h: CTL}/g; s/CTL SCLN/{t: ';', h: CTL}/g" "$tmp_yaml"
perl -0pi -e "s/{t: UNDS SYM, h: Symbol}/{t: '_', h: Symbol}/g; s/UNDS SYM/{t: '_', h: Symbol}/g; s/{t: SPACE, h: Media}/SPACE/g; s/{t: '~', type: trans}/'~'/g; s/ARROW/'->'/g" "$tmp_yaml"
perl -0pi -e "s/{t: ▽, h: MOD_LCTL, type: trans}/{t: ▽, type: trans}/g; s/{t: Gui\\+R, type: trans}/Cmd+R/g; s/Gui\\+R/Cmd+R/g; s/Ctl\\+Sft\\+TAB/Prev Tab/g; s/Ctl\\+TAB/Next Tab/g; s/Gui\\+\\[/Cmd+[/g; s/Gui\\+\\]/Cmd+]/g; s/{t: SRCHSEL, type: trans}/Search Sel/g; s/SRCHSEL/Search Sel/g; s/{t: DEL, type: trans}/DEL/g; s/{t: Gui\\+Z, type: trans}/Cmd+Z/g; s/Gui\\+Z/Cmd+Z/g; s/{t: Gui\\+X, type: trans}/Cmd+X/g; s/Gui\\+X/Cmd+X/g; s/Gui\\+C/Cmd+C/g; s/Gui\\+V/Cmd+V/g; s/Gui\\+Sft\\+V/Cmd+Shift+V/g; s/SELBack/Sel Word Back/g; s/SELWBAK/Sel Word Back/g; s/SELWORD/Sel Word/g; s/{t: SELLINE, type: trans}/Sel Line/g; s/SELLINE/Sel Line/g; s/{t: Gui\\+TAB, type: trans}/Cycle Tab/g; s/Gui\\+TAB/Cycle Tab/g; s/{t: QK LLCK, type: trans}/Layer Lock/g; s/QK LLCK/Layer Lock/g" "$tmp_yaml"
perl -0pi -e "s/{t: MS BTN1, type: trans}/Click/g; s/MS BTN1/Click/g; s/MS BTN2/Right Click/g; s/MS BTN3/Middle Click/g; s/MS BTN4/Back Btn/g; s/MS BTN5/Forward Btn/g; s/{t: Ctl\\+Gui\\+Sft\\+4, type: trans}/Area Copy/g; s/Ctl\\+Gui\\+Sft\\+4/Area Copy/g; s/{t: Ctl\\+Gui\\+Sft\\+3, type: trans}/Screen Copy/g; s/Ctl\\+Gui\\+Sft\\+3/Screen Copy/g; s/{t: Gui\\+Sft\\+Z, type: trans}/Redo/g; s/Gui\\+Sft\\+Z/Redo/g; s/{t: Gui\\+L, type: trans}/Cmd+L/g; s/Gui\\+L/Cmd+L/g" "$tmp_yaml"
perl -0pi -e "s/GESTURE/Gesture/g; s/NAVIGATOR DEC CPI/CPI-/g; s/NAVIGATOR INC CPI/CPI+/g; s/TOGGLE SCROLL/Scroll Toggle/g; s/DRAG SCROLL/Drag Scroll/g; s/{t: ▽, h: Mouse, type: trans}/Mouse Off/g; s/OSM\\(MOD_LCTL\\)/OSM CTL/g; s/OSM\\(MOD_LALT\\)/OSM ALT/g; s/OSM\\(MOD_LGUI\\)/OSM GUI/g; s/OSM\\(MOD_LSFT\\)/OSM SFT/g" "$tmp_yaml"
perl -0pi -e "s/{t: '\\|', type: trans}/'|'/g; s/{t: \\^, type: trans}/^/g; s/{t: '&', type: trans}/'&'/g; s/{t: '#', type: trans}/'#'/g; s/{t: \\+, type: trans}/+/g; s/{t: '\\[', type: trans}/'['/g; s/{t: '\\]', type: trans}/']'/g; s/{t: '%', type: trans}/'%'/g; s/{t: '@', type: trans}/'@'/g; s/{t: ':', type: trans}/':'/g; s/{t: ',', type: trans}/','/g; s/{t: \\., type: trans}/./g; s/{t: '''', type: trans}/''''/g" "$tmp_yaml"
perl -0pi -e "s/\{t: '\@', type: trans\}/'\@'/g" "$tmp_yaml"
cp "$tmp_yaml" docs/keymap.yaml
keymap draw docs/keymap.yaml -o docs/keymap.svg
