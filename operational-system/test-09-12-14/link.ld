OUTPUT_FORMAT("binary")
ENTRY(kmain)
phys = 0x8200;
SECTIONS
{
  .text phys : AT(phys) {
	code = .;
	*(.text);
  }
  .data : AT(phys + (data - code)) {
	data = .;
	*(.data);
  }
}
