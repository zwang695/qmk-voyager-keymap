# ZSA Voyager QMK Keymap

Personal QMK external userspace repository for the ZSA Voyager.

This repository intentionally contains only one keymap:

```text
keyboards/zsa/voyager/keymaps/zwang695
```

The keymap source is based on the Oryx export for `voyager-default-mac`:

```text
https://configure.zsa.io/voyager/layouts/lBWEb/ZPG0o5/0
```

It keeps the Oryx-generated `config.h`, `rules.mk`, and layout metadata while
building from this repository through QMK external userspace.

## Local Setup

Install the QMK CLI, then set up ZSA's QMK fork:

```sh
qmk setup zsa/qmk_firmware -b firmware25
```

Configure this repository as your QMK external userspace:

```sh
qmk config user.overlay_dir="$(realpath .)"
```

## Build

Compile the Voyager keymap directly:

```sh
qmk compile -kb zsa/voyager -km zwang695
```

Or compile all userspace targets from `qmk.json`:

```sh
qmk userspace-compile
```

GitHub Actions also builds this keymap against `zsa/qmk_firmware@firmware25`
on every push and manual workflow dispatch.
