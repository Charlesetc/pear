/* silver utils */

type position = {line: int, column: int};

let string_of_char = String.make 1;

let string_type_of_int i => {
  let number = i / 26;
  let append_str =
    if (number == 0) {
      ""
    } else {
      string_of_int number
    };
  "'" ^ string_of_char (Char.chr (i + Char.code 'a')) ^ append_str
};

let list_of_string string => {
  let lst = ref [];
  String.iter (fun c => lst := [c, ...!lst]) string;
  !lst
};

let last_of list => List.nth list (List.length list - 1);

/* This should be removed entirely - it's just a short term fix */
let rec all_but_last_of list =>
  switch list {
  | [] => []
  | [a] => []
  | [a, ...list] => [a, ...all_but_last_of list]
  };

let rec split_at index list =>
  if (index == 0) {
    ([], list)
  } else {
    let (first_list, second_list) = split_at (index - 1) (List.tl list);
    ([List.hd list, ...first_list], second_list)
  };

exception Silver_error of string position;

exception Silver_bug of string position;

let empty_silver_bug str => Silver_bug str {line: (-1), column: (-1)};

let empty_silver_error str => Silver_error str {line: (-1), column: (-1)};

let print_silver_error error =>
  switch error {
  | Silver_error desc pos => Printf.printf "line:%d, column:%d\n  %s\n" pos.line pos.column desc
  | Silver_bug desc pos =>
    Printf.printf "INTERNAL COMPILER ERROR\nline:%d, column:%d\n  %s\n" pos.line pos.column desc
  | _ =>
    print_string "unknown error:\n";
    Printexc.print_backtrace stderr;
    raise error
  };
