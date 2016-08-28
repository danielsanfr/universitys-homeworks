OUTPUT_FORMAT("binary")
ENTRY(kmain)
SECTIONS
{
  .text : {
	*(.text)
  }
  .data : { }
}
