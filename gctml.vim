" vim syntax file
" gert-ctml

if exists("b:current_syntax")
	finish
endif

syn match tagStart '\(^\|\s\)\[\(\S\+\|{.*}\)' contains=tagAttrib

syn match tagAttrib '\(\(\.\|\#\|@\)\S\+\|{.*}\)' contained

syn match tagEnd '\])\|\]'

let b:current_syntax = "gctml"

hi def link tagStart Constant
hi def link tagEnd Constant
hi def link tagAttrib Comment
