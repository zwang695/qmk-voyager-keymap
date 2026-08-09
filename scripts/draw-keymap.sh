#!/usr/bin/env bash
set -euo pipefail

export PATH="$HOME/.local/bin:/root/.local/bin:/home/zacha/.local/bin:$PATH"

tmp_dir="$(mktemp -d)"
cleanup() {
  rm -rf -- "$tmp_dir"
}
trap cleanup EXIT

normalize_yaml() {
  local yaml_file="$1"
  local platform="$2"

  perl -0pi -e 's/layout_name: LAYOUT_voyager/layout_name: LAYOUT/' "$yaml_file"
  perl -0pi -e "s/ESCAPE/ESC/g; s/LEFT CTRL/LCTL/g; s/RIGHT GUI/RGUI/g; s/{t: CTL A, h: CTL}/{t: A, h: CTL}/g; s/CTL A/{t: A, h: CTL}/g; s/{t: OPT S, h: OPT}/{t: S, h: OPT}/g; s/OPT S/{t: S, h: OPT}/g; s/{t: CMD D, h: CMD}/{t: D, h: CMD}/g; s/CMD D/{t: D, h: CMD}/g; s/SYM F/{t: F, h: Symbol}/g; s/SYM J/{t: J, h: Symbol}/g; s/{t: CMD K, h: CMD}/{t: K, h: CMD}/g; s/CMD K/{t: K, h: CMD}/g; s/{t: OPT L, h: OPT}/{t: L, h: OPT}/g; s/OPT L/{t: L, h: OPT}/g; s/{t: CTL SCLN, h: CTL}/{t: ';', h: CTL}/g; s/CTL SCLN/{t: ';', h: CTL}/g" "$yaml_file"
  perl -0pi -e "s/{t: UNDS SYM, h: Symbol}/{t: '_', h: Symbol}/g; s/UNDS SYM/{t: '_', h: Symbol}/g; s/{t: SPACE, h: Media}/SPACE/g; s/{t: '~', type: trans}/'~'/g; s/ARROW/'->'/g" "$yaml_file"
  perl -0pi -e "s/{t: ▽, h: MOD_LCTL, type: trans}/{t: ▽, type: trans}/g; s/{t: Gui\+R, type: trans}/Cmd+R/g; s/Gui\+R/Cmd+R/g; s/Ctl\+Sft\+TAB/Prev Tab/g; s/Ctl\+TAB/Next Tab/g; s/Gui\+\[/Cmd+[/g; s/Gui\+\]/Cmd+]/g; s/{t: SRCHSEL, type: trans}/Search Sel/g; s/SRCHSEL/Search Sel/g; s/{t: DEL, type: trans}/DEL/g; s/{t: Gui\+Z, type: trans}/Cmd+Z/g; s/Gui\+Z/Cmd+Z/g; s/{t: Gui\+X, type: trans}/Cmd+X/g; s/Gui\+X/Cmd+X/g; s/Gui\+C/Cmd+C/g; s/Gui\+V/Cmd+V/g; s/Gui\+Sft\+V/Cmd+Shift+V/g; s/SELBack/Sel Word Back/g; s/SELWBAK/Sel Word Back/g; s/SELWORD/Sel Word/g; s/{t: SELLINE, type: trans}/Sel Line/g; s/SELLINE/Sel Line/g; s/{t: Gui\+TAB, type: trans}/Cycle Tab/g; s/Gui\+TAB/Cycle Tab/g; s/{t: QK LLCK, type: trans}/Layer Lock/g; s/QK LLCK/Layer Lock/g" "$yaml_file"
  perl -0pi -e "s/{t: MS BTN1, type: trans}/Click/g; s/MS BTN1/Click/g; s/MS BTN2/Right Click/g; s/MS BTN3/Middle Click/g; s/MS BTN4/Back Btn/g; s/MS BTN5/Forward Btn/g; s/{t: Ctl\+Gui\+Sft\+4, type: trans}/Area Copy/g; s/Ctl\+Gui\+Sft\+4/Area Copy/g; s/{t: Ctl\+Gui\+Sft\+3, type: trans}/Screen Copy/g; s/Ctl\+Gui\+Sft\+3/Screen Copy/g; s/{t: Gui\+Sft\+Z, type: trans}/Redo/g; s/Gui\+Sft\+Z/Redo/g; s/{t: Gui\+L, type: trans}/Cmd+L/g; s/Gui\+L/Cmd+L/g" "$yaml_file"
  perl -0pi -e "s/NAVIGATOR DEC CPI/CPI-/g; s/NAVIGATOR INC CPI/CPI+/g; s/TOGGLE SCROLL/Scroll Toggle/g; s/DRAG SCROLL/Drag Scroll/g" "$yaml_file"
  perl -0pi -e "s/{t: '\|', type: trans}/'|'/g; s/{t: \^, type: trans}/^/g; s/{t: '&', type: trans}/'&'/g; s/{t: '#', type: trans}/'#'/g; s/{t: \+, type: trans}/+/g; s/{t: '\[', type: trans}/'['/g; s/{t: '\]', type: trans}/']'/g; s/{t: '%', type: trans}/'%'/g; s/{t: '@', type: trans}/'@'/g; s/{t: ':', type: trans}/':'/g; s/{t: ',', type: trans}/','/g; s/{t: \., type: trans}/./g; s/{t: '''', type: trans}/''''/g" "$yaml_file"
  perl -0pi -e "s/\{t: '\@', type: trans\}/'\@'/g" "$yaml_file"

  if [[ "$platform" == "linux" ]]; then
    perl -0pi -e "s/GUI A/{t: A, h: GUI}/g; s/ALT S/{t: S, h: ALT}/g; s/CTL D/{t: D, h: CTL}/g; s/CTL K/{t: K, h: CTL}/g; s/ALT L/{t: L, h: ALT}/g; s/GUI SCLN/{t: ';', h: GUI}/g; s/ALT R/{t: R, h: ALT}/g; s/CTL S/{t: S, h: CTL}/g; s/SYM T/{t: T, h: Symbol}/g; s/SYM N/{t: N, h: Symbol}/g; s/CTL E/{t: E, h: CTL}/g; s/ALT I/{t: I, h: ALT}/g; s/GUI O/{t: O, h: GUI}/g" "$yaml_file"
    perl -0pi -e "s/Ctl\+R/Ctrl+R/g; s/Alt\+LEFT/Back/g; s/Alt\+RIGHT/Forward/g; s/Ctl\+Sft\+Z/Redo/g; s/Ctl\+Z/Undo/g; s/Ctl\+C/Ctrl+C/g; s/Ctl\+V/Ctrl+V/g; s/Ctl\+Sft\+V/Ctrl+Shift+V/g; s/Ctl\+L/Ctrl+L/g; s/Sft\+PSCR/Area Copy/g; s/PSCR/Screen Copy/g; s/Alt\+TAB/Cycle App/g; s/TG\(L COLEMAK\)/Switch Layout/g" "$yaml_file"
  fi
}

generate_diagram() {
  local keymap_name="$1"
  local output_name="$2"
  local platform="$3"
  shift 3

  local tmp_json="$tmp_dir/$keymap_name.json"
  local tmp_yaml="$tmp_dir/$keymap_name.yaml"

  qmk c2json --no-cpp \
    -kb zsa/voyager \
    -km "$keymap_name" \
    "keyboards/zsa/voyager/keymaps/$keymap_name/keymap.c" \
    -o "$tmp_json"

  keymap parse \
    -c 12 \
    --layer-names "$@" \
    -q "$tmp_json" \
    -o "$tmp_yaml"

  normalize_yaml "$tmp_yaml" "$platform"
  cp "$tmp_yaml" "docs/$output_name.yaml"
  keymap draw "docs/$output_name.yaml" -o "docs/$output_name.svg"
}

generate_diagram zwang695 keymap mac Base Symbol Cursor Num Magic
generate_diagram zwang695_linux keymap-linux linux QWERTY Colemak-DH Symbol Cursor Num Magic
