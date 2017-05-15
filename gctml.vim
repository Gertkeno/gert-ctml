" vim syntax file
" gert-ctml

if exists("b:current_syntax")
	finish
endif

syn match tagStart '\v(^|\s)\[(\S+|\{.*\})' contains=tagAttrib
syn match tagAttrib '\v((\.|\$|\#|\@)\S+|\{.*\})' contained
syn match tagEnd '\v\\=(]\)|])' contains=escaped
syn match escaped '\\.'

let b:current_syntax = "gctml"

hi def link tagStart Constant
hi def link tagEnd Constant
hi def link tagAttrib Comment
hi def link escaped Normal
