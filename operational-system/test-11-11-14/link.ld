OUTPUT_FORMAT("binary")
ENTRY(kmain)
phys = 0x8400;
SECTIONS
{
  .text phys : AT(phys) {
	*(.text)
  }
  .data : { }
}
