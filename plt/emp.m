Nx= 1024;
Ny= 1024;
Nz= 1;
NF= 1;
TS= 0;
for i= 1:1:NF
	name= sprintf('emp-%d.png', i);
	file= sprintf('../dat/phi-%d.dat', i);
	data= load(file);
	l= 1;
	for a= 1:1:Nx
		for b= 1:1:Ny
			for c= 1:1:Nz
				m(a, b, c)= data(l, 1);
				l= l+1;
			end
		end
	end
	h= figure;
	set(h, 'visible', 'off');
	set(gcf, 'Renderer', 'zbuffer')
	axes_S= axes('Parent', h         ,...
	             'XTick' , zeros(1,0),...
	             'YTick' , zeros(1,0),...
	             'ZTick' , zeros(1,0));
	S= patch(isosurface(m, TS), 'FaceColor', ...
                              'blue', 'EdgeColor', 'none');
	isonormals(m, S)
	view(1028,-347)
	axis tight
	camlight
	lighting phong
	box on
	grid off
	xlim([1 Nx])
	ylim([1 Ny])
	zlim([1 Nz])
%	annotation(h, 'arrow', [0.644 0.644], [0.540 0.460], 'Color', [0 0 1]);
	print(name, '-dpng')
end
