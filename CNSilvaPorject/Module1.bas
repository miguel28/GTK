Attribute VB_Name = "Module1"
Option Explicit
Public Name As String
Public NameCounter As Byte
Public PartWidth As Integer
Public PartHeight As Integer
Public StartProgram As String
Public EndProgram As String
Public Program As String
Public Zoom As Byte
Public File As String



Sub Main()
NameCounter = 1
PartWidth = 50
PartHeight = 80
Zoom = 6
Name = "Sin Titulo " & Str(NameCounter)
MainForm.Show
End Sub
