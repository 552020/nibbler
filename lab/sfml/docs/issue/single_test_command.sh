unset CAML_LD_LIBRARY_PATH && ./sfml-app & sleep 2 && kill %1 2>/dev/null; export CAML_LD_LIBRARY_PATH=/Users/stefano/.opam/default/lib/stublibs:/Users/stefano/.opam/default/lib/ocaml/stublibs:/Users/stefano/.opam/default/lib/ocaml && unset DISPLAY && ./sfml-app & sleep 2 && kill %1 2>/dev/null; export DISPLAY=/private/tmp/com.apple.launchd.gxVclvPuiQ/org.xquartz:0 && unset VSCODE_INJECTION && ./sfml-app & sleep 2 && kill %1 2>/dev/null; export VSCODE_INJECTION=1 && unset MallocNanoZone && ./sfml-app & sleep 2 && kill %1 2>/dev/null; export MallocNanoZone=0 && unset OPAM_LAST_ENV && ./sfml-app & sleep 2 && kill %1 2>/dev/null; export OPAM_LAST_ENV=/Users/stefano/.opam/.last-env/env-59ac0b36b1c224a2d17ef2e4eb3bd1ec-0 && echo "Test complete - check which one worked"



