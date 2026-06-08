# Agent Instructions

- After editing `keyboards/zsa/voyager/keymaps/zwang695/keymap.c`, run `scripts/draw-keymap.sh` and include any resulting `docs/keymap.yaml` and `docs/keymap.svg` changes.
- Before pushing, run `scripts/hooks/pre-push` or configure the repo with `git config core.hooksPath scripts/hooks` so the diagram check runs automatically.
- Verify firmware changes with `qmk compile -kb zsa/voyager -km zwang695`.
