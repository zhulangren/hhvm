(** This is a dune configurator:
https://jbuilder.readthedocs.io/en/latest/configurator.html *)

module C = Configurator.V1

let find_hphp_parent dir =
  let path = String.split_on_char '/' dir in
  let rec reconstruct_till_hphp path acc =
    match path with
    | [] -> acc
    | "hphp" :: path ->
      if List.mem "hphp" path
      then reconstruct_till_hphp path (acc ^ "hphp/")
      else acc
    | dir :: path ->
      let acc = acc ^ dir ^ "/" in
      reconstruct_till_hphp path acc in
  reconstruct_till_hphp path ""

let () =
  C.main ~name:"hphpdir" (fun (_c : C.t) ->
    let source_root = match Sys.getenv "CMAKE_SOURCE_DIR" with
    | t -> t^"/"
    | exception Not_found ->
      let workingdir = Sys.getcwd () in
      find_hphp_parent workingdir
    in
    C.Flags.write_lines "hphp_parent" [ source_root ])
