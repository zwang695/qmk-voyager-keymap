# ZSA Voyager QMK Keymap

Personal QMK external userspace repository for the ZSA Voyager.

This repository contains separate macOS and Linux keymaps:

```text
keyboards/zsa/voyager/keymaps/zwang695        # macOS
keyboards/zsa/voyager/keymaps/zwang695_linux  # Linux, QWERTY + Colemak-DH
```

The keymap source is based on the Oryx export for `voyager-default-mac`:

```text
https://configure.zsa.io/voyager/layouts/lBWEb/ZPG0o5/0
```

It keeps the Oryx-generated `config.h`, `rules.mk`, and layout metadata while
building from this repository through QMK external userspace.

## Keymap Diagrams

### macOS

![Voyager macOS keymap](docs/keymap.svg?raw=1)

### Linux

![Voyager Linux keymap](docs/keymap-linux.svg?raw=1)

The Go60-to-Voyager physical-subset diff is documented in
[`docs/go60-voyager-diff.md`](docs/go60-voyager-diff.md).

The diagrams are generated with
[`keymap-drawer`](https://github.com/caksoylar/keymap-drawer). After setting up
the QMK CLI below, install `keymap-drawer` and redraw with:

```sh
pipx install keymap-drawer
scripts/draw-keymap.sh
```

To keep diagrams fresh before pushes, enable the checked-in Git hook:

```sh
git config core.hooksPath scripts/hooks
```

The hook runs `scripts/draw-keymap.sh` and blocks the push if either generated
diagram needs to be committed.

## Local Setup

Install the QMK CLI, then set up ZSA's QMK fork. This keymap uses ZSA
Navigator/Automouse support for the Voyager trackball layer, so it should be
built against `zsa/qmk_firmware`.

```sh
qmk setup zsa/qmk_firmware
```

Configure this repository as your QMK external userspace:

```sh
qmk config user.overlay_dir="$(realpath .)"
```

## Build

Compile the Voyager keymap directly:

```sh
# macOS
qmk compile -kb zsa/voyager -km zwang695

# Linux
qmk compile -kb zsa/voyager -km zwang695_linux
```

The Linux keymap keeps the Voyager controls from the macOS keymap, uses Linux
`Ctrl`/`Alt` shortcuts, and adds Colemak-DH. Hold the bottom-left Magic key and
tap the physical `F` key to switch from QWERTY to Colemak-DH; use the same
physical key (`T` in Colemak-DH) to switch back.

Or compile all userspace targets from `qmk.json`:

```sh
qmk userspace-compile
```

GitHub Actions also builds this keymap against `zsa/qmk_firmware@master`
on every push and manual workflow dispatch.
