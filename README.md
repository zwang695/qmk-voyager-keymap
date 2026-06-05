# ZSA Voyager QMK Keymap

Personal QMK external userspace repository for the ZSA Voyager.

This repository intentionally contains only one keymap:

```text
keyboards/zsa/voyager/keymaps/zwang695
```

The first version is based on ZSA's default Voyager keymap from
`zsa/qmk_firmware` on the `firmware25` branch.

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
