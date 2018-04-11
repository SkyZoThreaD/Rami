.PHONY: clean All

All:
	@echo "----------Building project:[ Rami - Debug_Lin ]----------"
	@"$(MAKE)" -f  "Rami.mk"
clean:
	@echo "----------Cleaning project:[ Rami - Debug_Lin ]----------"
	@"$(MAKE)" -f  "Rami.mk" clean
